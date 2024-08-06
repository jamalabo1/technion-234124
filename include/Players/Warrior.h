//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_WARRIOR_H
#define TECHNION_234124_WARRIOR_H

#include <memory>

#include "Player.h"

class Warrior : public Player {
public:
    Warrior(string name, std::unique_ptr<Strategy>);

    void postCombat(bool battleWon) override;

    int getCombatPower() const override;
};


#endif //TECHNION_234124_WARRIOR_H
