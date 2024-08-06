//
// Created by jamal on 03/08/2024.
//
#include <Players/Magician.h>

Magician::Magician(string name, unique_ptr<Strategy> strategy) : Player(name, strategy, "Magician") {
}

int Magician::experienceSolarEclipse() {
    addForce(1);
    return 1;
}
