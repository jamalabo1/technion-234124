//
// Created by jamal on 03/08/2024.
//
#include <Players/Archer.h>

Archer::Archer(string name, unique_ptr<Strategy> strategy) : Player(name, strategy, "Archer")
{
    setCoins(20);
}
