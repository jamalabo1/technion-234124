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

template<typename T, typename Func>
int accumulate(std::vector<T> vec, Func func) {
    int result = 0;
    for (const auto &item: vec) {
        result += func(item);
    }
    return result;
}

Pack::Pack(const vector<shared_ptr<Monster>> &pack) : Monster(
        "Pack",
        ACCUMULATE_VECTOR(pack, getLoot),
        ACCUMULATE_VECTOR(pack, getDamage),
        ACCUMULATE_VECTOR(pack, getCombatPower)
), pack(pack) {

}

#include <iostream>

string Pack::getDescription() const {



//    std::cout << "------ START PACK " << this << "------" << std::endl;
//    for (int i = 0; i < pack.size(); i++) {
//        std::cout << pack[i]->getDescription() << std::endl;
//    }
//    std::cout << "------END PACK" << this << "------" << std::endl;

    string desc = "[";

    for (size_t i = 0; i < pack.size(); i++) {
        if (pack[i]->getKey() == "Pack") {
            desc += pack[i]->getDescription();
        } else {
            desc += "\"" + pack[i]->getKey() + "\"";
        }
        if (i != pack.size() - 1) desc += ",";
    }

    desc += "]";
    return desc;

//    return "Pack of " + to_string(pack.size()) + " members " + generalStats();
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

    setLoot(ACCUMULATE_VECTOR(pack, getLoot));
    setDamage(ACCUMULATE_VECTOR(pack, getDamage));
    setCombatPower(ACCUMULATE_VECTOR(pack, getCombatPower));
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
            return make_shared<EncounterEvent>(Monster::createType(key, args));
        });
    }
}


void Balrog::postCombat() {
    addCombatPower(2);
}


class Tree {
public:
    vector<Tree> nodes;
    shared_ptr<Monster> item;
    string key;

    Tree(const shared_ptr<Monster> &item, string key) : nodes(), item(item), key(key) {}

    Tree(const vector<Tree> &nodes, const shared_ptr<Monster> &item, string key) : nodes(nodes), item(item), key(key) {}
};


tuple<int, shared_ptr<Monster>> createTree(const std::vector<string> &arguments, int offsetStart) {
    if (arguments[offsetStart] == "Pack") {
        int length = atoi(arguments[offsetStart + 1].c_str());
        int endOffset = offsetStart + 2;
        vector<shared_ptr<Monster>> nodes;
        for (int i = 0; i < length; i++) {
            string key = arguments[endOffset];
            if (key == "Pack") {
                auto [offsetEnd, tree] = createTree(arguments, endOffset);
                endOffset = offsetEnd;
                nodes.emplace_back(tree);
            } else {
//                Tree tree(Monster::createType(key, arguments), key);
                endOffset++;
                nodes.emplace_back(
                        Monster::createType(key, arguments)
                );
            }
        }

//        vector<shared_ptr<Monster>> monstersPack;
//        monstersPack.reserve(nodes.size());
//        for (const auto &item: nodes) {
//            monstersPack.emplace_back(item.item);
//        }

        auto pack = make_shared<Pack>(nodes);
//        Tree tree(nodes, pack, "Pack");
        return std::pair(endOffset, pack);
    } else {
        return std::pair(offsetStart,
                         Monster::createType(arguments[offsetStart], arguments)
        );
    }
}

IMPLEMENT_FACTORY_REGISTER(Pack) {
    registerFactory("Pack",
                    [](const vector<string> &arguments) {
                        auto [_, tree] = createTree(arguments, 0);

                        return tree;
                    });
}


GENERIC_MONSTER_REGISTER(Snail);
GENERIC_MONSTER_REGISTER(Slime);
GENERIC_MONSTER_REGISTER(Balrog);
