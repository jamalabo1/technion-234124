//
// Created by jamal on 03/08/2024.
//
#include <Events/EncounterEvent.h>
#include <memory>
#include <stdexcept>
#include "../../Utilities.h"

using std::to_string;
using std::make_shared;
using std::shared_ptr;
using std::vector;
using std::map;

template<typename T, typename Func>
int accumulate(std::vector<T> vec, Func func) {
    int result = 0;
    for (const auto &item: vec) {
        result += func(item);
    }
    return result;
}

#define ACCUMULATE_VECTOR(vec, func) accumulate(pack, [](auto x) { return x->func(); })

template
class Factorable<Monster>;


Monster::Monster(string key, int loot, int damage, int combatPower) : key(key), loot(loot), damage(damage),
                                                                      combatPower(combatPower) {


}


int Monster::getCombatPower() const {
    return combatPower;
}

int Monster::getDamage() const {
    return damage;
}

int Monster::getLoot() const {
    return loot;
}

string Monster::getKey() const {
    return key;
}

string Monster::getDescription() const {
    return getKey() + " " + generalStats();

}

string Monster::generalStats() const {
    return "(power " + to_string(getCombatPower()) +
           ", loot " + to_string(getLoot()) +
           ", damage " + to_string(getDamage())
           + ")";
}

void Monster::postCombat() {
    // default behaviour: no-effect
}

void Monster::addCombatPower(const int &quantity) {
    combatPower += quantity;
}

void Monster::setLoot(const int &qty) {
    loot = qty;
}

void Monster::setCombatPower(const int &qty) {
    combatPower = qty;
}

void Monster::setDamage(const int &qty) {
    damage = qty;
}

Snail::Snail() : Monster("Snail", 2, 10, 5) {}

Slime::Slime() : Monster("Slime", 5, 25, 12) {}

Balrog::Balrog() : Monster("Balrog", 100, 9001, 15) {}


Pack::Pack(const vector<shared_ptr<Monster>> &pack) : Monster(
        "Pack",
        ACCUMULATE_VECTOR(pack, getLoot),
        ACCUMULATE_VECTOR(pack, getDamage),
        ACCUMULATE_VECTOR(pack, getCombatPower)
), pack(pack) {

}

string Pack::getDescription() const {
    return "Pack of " + to_string(pack.size()) + " members " + generalStats();
}

void Pack::postCombat() {
    for (auto &item: pack) {
        item->postCombat();
    }

    setLoot(ACCUMULATE_VECTOR(pack, getLoot));
    setDamage(ACCUMULATE_VECTOR(pack, getDamage));
    setCombatPower(ACCUMULATE_VECTOR(pack, getCombatPower));
}


EncounterEvent::EncounterEvent(shared_ptr<Monster> monster) : monster(monster) {

}

string EncounterEvent::applyTo(shared_ptr<Player> player) {
    const bool playerWon = player->getCombatPower() > monster->getCombatPower();

    if (playerWon) {
        player->levelUp();
        player->addCoins(monster->getLoot());
    } else {
        player->loseHp(monster->getDamage());
    }
    player->postCombat(playerWon);
    monster->postCombat();

    if (!playerWon) {
        return getEncounterLostMessage(*player, monster->getDamage());
    }

    return getEncounterWonMessage(*player, monster->getLoot());
}

string EncounterEvent::getDescription() const {
    return monster->getDescription();
}

// behaves like a static register for the type.
IMPLEMENT_FACTORY_REGISTER(EncounterEvent) {
    // import most factories
    for (const auto &key: Monster::getFactoryKeys()) {
        registerFactory(key, [key](const std::vector<string> &args) {
            // could've used the provided factory, but it's the Monster responsibility to call the factory.
            auto monsterInfo = Monster::createType(key, args);
            return make_tuple(make_shared<EncounterEvent>(std::get<0>(monsterInfo)), std::get<1>(monsterInfo));
        });
    }
}


void Balrog::postCombat() {
    addCombatPower(2);
}

int parseInt(string str) {
    // trim leading zeros
    int endIndex = 0;
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == '0') {
            endIndex = i + 1;
        } else {
            break;
        }
    }
    string nstr = str.substr(endIndex, (str.size() - endIndex));

    uint val = std::stoul(nstr);
    if (to_string(val) != nstr) {
        throw std::invalid_argument("value is not double");
    }
    return val;
}

tuple<shared_ptr<Monster>, int> createTree(const std::vector<string> &arguments, int offsetStart) {
    if (arguments[offsetStart] == "Pack") {
        if ((offsetStart - 2) == (int) arguments.size()) {
            throw std::invalid_argument("invalid arguments size");
        }

        int length = parseInt(arguments[offsetStart + 1]);


        int endOffset = offsetStart + 2;
        vector<shared_ptr<Monster>> nodes;

        for (int i = 0; i < length; i++) {

            if (endOffset >= (int) arguments.size()) {
                throw std::invalid_argument("end offset is invalid");
            }

            string key = arguments[endOffset];
            if (key == "Pack") {
                auto treeInfo = createTree(arguments, endOffset);
                endOffset = std::get<1>(treeInfo);
                nodes.emplace_back(std::get<0>(treeInfo));
            } else {
                endOffset++;
                auto [item, _] = Monster::createType(key, arguments);
                nodes.emplace_back(
                        item
                );
            }
        }

        auto pack = make_shared<Pack>(nodes);
        return std::pair(pack, endOffset);
    }

    return Monster::createType(arguments[offsetStart], arguments);
}

IMPLEMENT_FACTORY_REGISTER(Pack) {
    registerFactory("Pack",
                    [](const vector<string> &arguments) {
                        try {
                            return createTree(arguments, 0);
                        } catch (std::exception &) {
                            throw std::invalid_argument("cannot create tree");
                        }
                    });
}


GENERIC_MONSTER_REGISTER(Snail);
GENERIC_MONSTER_REGISTER(Slime);
GENERIC_MONSTER_REGISTER(Balrog);
