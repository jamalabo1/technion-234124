//
// Created by jamal on 03/08/2024.
//
#include "Archer.h"

using std::make_shared;
using std::vector;

Archer::Archer(string name, shared_ptr<Strategy> strategy) : Player(std::move(name), std::move(strategy), Archer::Key) {
    setCoins(20);
}

GENERIC_PLAYER_REGISTER(Archer);