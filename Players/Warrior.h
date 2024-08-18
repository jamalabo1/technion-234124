//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_WARRIOR_H
#define TECHNION_234124_WARRIOR_H

#include <memory>

#include "Player.h"

class Warrior : public Player {
private:
    CREATE_FACTORY_REGISTER();

    static const int MAX_HEALTH = 150;

public:
    Warrior(string name, std::shared_ptr<Strategy>);

    void postCombat(bool battleWon) override;

    int getCombatPower() const override;

    static inline string Key = "Warrior";
};


#endif //TECHNION_234124_WARRIOR_H