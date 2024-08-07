//
// Created by jamal on 03/08/2024.
//
#include <Players/Warrior.h>


Warrior::Warrior(string name, shared_ptr<Strategy> strategy) : Player(name, strategy, Warrior::Key)
{
    setMaxHealth(150);
    setHealth(150);
}

void Warrior::postCombat(bool battleWon)
{
    loseHp(10);
}

int Warrior::getCombatPower() const
{
    return 2 * getForce() + getLevel();
}

GENERIC_REGISTER(Warrior);
