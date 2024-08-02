//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_WARRIOR_H
#define TECHNION_234124_WARRIOR_H

#include "Player.h"

class Warrior : Player {
    int CombatPower;
public:
   Warrior(){
       max_HP = 150;
       current_HP = max_HP;
       CombatPower = Force *2 + Level;
   }

};

#endif //TECHNION_234124_WARRIOR_H
