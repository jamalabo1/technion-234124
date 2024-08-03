//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_ARCHER_H
#define TECHNION_234124_ARCHER_H
#include "Player.h"

class Archer : Player
{
public:
    Archer(unique_ptr<Strategy>& strategy);
};

#endif //TECHNION_234124_ARCHER_H
