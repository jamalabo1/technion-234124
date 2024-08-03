//
// Created by jamal on 03/08/2024.
//
#include <Players/Archer.h>

Archer::Archer(unique_ptr<Strategy>& strategy) : Player(strategy, "Archer", "Archer")
{
    setCoins(20);
}
