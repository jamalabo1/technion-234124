//
// Created by jamal on 03/08/2024.
//
#include <Players/Warrior.h>


Warrior::Warrior(unique_ptr<Strategy>& strategy) : Player(strategy, "Warrior", "Warrior")
{
    setMaxHealth(150);
}

void Warrior::postCombat(bool battleWon)
{
    loseHp(10);
}

int Warrior::getCombatPower() const
{
    return 2 * getForce() + getLevel();
}
