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


#define ACCUMULATE_VECTOR(vec, func) accumulate(pack, [](auto x) { return x->func(); })

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

Snail::Snail() : Monster("Snail", 2, 10, 5) {}

Slime::Slime() : Monster("Slime", 5, 25, 12) {}

Balrog::Balrog() : Monster("Balrog", 100, 9001, 15) {}

template<typename T, typename Func>
int accumulate(std::vector<T> vec, Func func) {
    int result = 0;
    for (const auto &item: vec) {
        result += func(item);
    }
    return result;
}

Pack::Pack(const vector<shared_ptr<Monster>> &pack) : Monster(
        "pack",
        ACCUMULATE_VECTOR(pack, getLoot),
        ACCUMULATE_VECTOR(pack, getDamage),
        ACCUMULATE_VECTOR(pack, getCombatPower)
), pack(pack) {

}

string Pack::getDescription() const {
    return "Pack of " + to_string(pack.size()) + " members " + generalStats();
}

// just update on post combat.
//int Pack::getLoot() const {
//    return ACCUMULATE_VECTOR(pack, getLoot);
//}
//
//int Pack::getDamage() const {
//    return ACCUMULATE_VECTOR(pack, getDamage);
//}
//
//int Pack::getCombatPower() const {
//    return ACCUMULATE_VECTOR(pack, getCombatPower);
//}

void Pack::postCombat() {
    for (auto &item: pack) {
        item->postCombat();
    }

    loot = ACCUMULATE_VECTOR(pack, getLoot);
    damage = ACCUMULATE_VECTOR(pack, getDamage);
    combatPower = ACCUMULATE_VECTOR(pack, getCombatPower);
}


EncounterEvent::EncounterEvent(shared_ptr<Monster> monster) : monster(monster) {

}

string EncounterEvent::applyTo(shared_ptr<Player> player) {
    const bool playerWon = player->getCombatPower() >= monster->getCombatPower();

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
    // TODO: check if really got levels.
    return getEncounterWonMessage(*player, monster->getLoot());
}

string EncounterEvent::getDescription() const {
    return monster->getDescription();
}

// behaves like a static register for the type.
IMPLEMENT_FACTORY_REGISTER(EncounterEvent) {
    // import most factories
    for (const auto &key: Monster::getFactoryKeys()) {
        registerFactory(key, FactorableTypeInfo([key](const std::vector<string> &args) {
            // could've used the provided factory, but it's the Monster responsible to call the factory.
            return make_shared<EncounterEvent>(Monster::createType(key, args));
        }));
    }
}


void Balrog::postCombat() {
    combatPower += 2;
}


IMPLEMENT_FACTORY_REGISTER(Pack) {
    registerFactory(
            "Pack",
            [](const std::vector<string> &arguments) {

                if (arguments.empty()) {
                    throw std::invalid_argument("");
                }


                // if size is 1 then there is a problem
                if (arguments.size() == 1) {
                    throw std::invalid_argument("");
                }


                int length = std::atoi(arguments[0].c_str());
                vector<shared_ptr<Monster>> monsterPack;
                for (int i = 0; i < length; i++) {
                    const string &monsterKey = arguments[1 + i];

                    monsterPack.emplace_back(
                            Monster::createType(monsterKey, arguments)
                    );
                }
                return make_shared<Pack>(monsterPack);
            }
    );
}

GENERIC_MONSTER_REGISTER(Snail);
GENERIC_MONSTER_REGISTER(Slime);
GENERIC_MONSTER_REGISTER(Balrog);
