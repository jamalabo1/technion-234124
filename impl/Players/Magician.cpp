//
// Created by jamal on 03/08/2024.
//
#include <Players/Magician.h>

Magician::Magician(unique_ptr<Strategy> &strategy) : Player(strategy, "Magician", "Magician") {
}

void Magician::experienceSolarEclipse() {
    addHp(1);
}
