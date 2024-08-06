//
// Created by jamal on 03/08/2024.
//
#include <Events/EncounterEvent.h>
#include <memory>
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


map<string, Monster::ptr> Monster::getMonsters() {
    static Monster snail("Snail", 2, 10, 5);
    static Monster slime("Slime", 5, 25, 12);
    static Monster balrog("Balrog", 100, 9001, 15);

//    static auto snailPtr = shared_ptr<const Monster>(&snail);

//    static Monster::ptr snailPtr = shared_ptr<const Monster>(&snail);
//    static Monster::ptr slimePtr = shared_ptr<const Monster>(&slime);
//    static Monster::ptr barlogPtr = shared_ptr<const Monster>(&barlog);
//

    // to disable the ability to free the instances, since they are static.
    return {
            {snail.getKey(),  Monster::ptr(Monster::ptr{}, &snail)},
            {slime.getKey(),  Monster::ptr(Monster::ptr{}, &slime)},
            {balrog.getKey(), Monster::ptr(Monster::ptr{}, &balrog)}
    };
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

Monster::Monster(const Monster &base, int length) : Monster(
        base.getKey(),
        base.getLoot() * length,
        base.getDamage() * length,
        base.getCombatPower() * length
) {

}

template<typename T, typename Func>
int accumulate(std::vector<T> vec, Func func) {
    int result = 0;
    for (const auto &item: vec) {
        result += func(item);
    }
    return result;
}

Pack::Pack(const vector<Monster::ptr> &pack) : Monster(
        "pack",
        ACCUMULATE_VECTOR(pack, getLoot),
        ACCUMULATE_VECTOR(pack, getDamage),
        ACCUMULATE_VECTOR(pack, getCombatPower)
), length(pack.size()) {

}

string Pack::getDescription() const {
    return "Pack of " + to_string(length) + " members " + generalStats();
}


EncounterEvent::EncounterEvent(Monster::ptr monster) : monster(monster) {

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

    if (!playerWon) {
        return getEncounterLostMessage(*player, monster->getDamage());
    }
    // TODO: check if really got levels.
    return getEncounterWonMessage(*player, monster->getLoot());
}

string EncounterEvent::getDescription() const {
    return monster->getDescription();
}

