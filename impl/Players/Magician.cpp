//
// Created by jamal on 03/08/2024.
//
#include <Players/Magician.h>

#include <utility>

Magician::Magician(string name, shared_ptr<Strategy> strategy) : Player(std::move(name), std::move(strategy), Magician::Key) {
}

int Magician::experienceSolarEclipse() {
    addForce(1);
    return 1;
}

GENERIC_PLAYER_REGISTER(Magician);
