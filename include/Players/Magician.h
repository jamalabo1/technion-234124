//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_MAGICIAN_H
#define TECHNION_234124_MAGICIAN_H

#include "Player.h"


class Magician : public  Player
{
public:
    Magician(string name, unique_ptr<Strategy>);

    int experienceSolarEclipse() override;
};

#endif //TECHNION_234124_MAGICIAN_H
