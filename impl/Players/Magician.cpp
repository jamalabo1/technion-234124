//
// Created by jamal on 03/08/2024.
//
#include <Players/Magician.h>

Magician::Magician(string name, shared_ptr<Strategy> strategy) : Player(name, strategy, Magician::Key) {
}

int Magician::experienceSolarEclipse() {
    addForce(1);
    return 1;
}

GENERIC_REGISTER(Magician);
