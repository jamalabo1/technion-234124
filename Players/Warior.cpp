//
// Created by jamal on 03/08/2024.
//
#include "Warrior.h"


Warrior::Warrior(string name, shared_ptr<Strategy> strategy) : Player(std::move(name), std::move(strategy),
                                                                      Warrior::Key) {
    setMaxHealth(MAX_HEALTH);
    setHealth(MAX_HEALTH);
}

void Warrior::postCombat(bool battleWon) {
    if (battleWon) {
        loseHp(10);
    }
}

int Warrior::getCombatPower() const {
    return 2 * getForce() + getLevel();
}

GENERIC_PLAYER_REGISTER(Warrior);
