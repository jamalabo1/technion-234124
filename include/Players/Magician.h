//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_MAGICIAN_H
#define TECHNION_234124_MAGICIAN_H

#include "Player.h"


class Magician : Player
{
public:
    Magician(unique_ptr<Strategy>&);
};

#endif //TECHNION_234124_MAGICIAN_H
