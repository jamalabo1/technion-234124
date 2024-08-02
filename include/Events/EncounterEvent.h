//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_ENCOUNTEREVENT_H
#define TECHNION_234124_ENCOUNTEREVENT_H

#include "Event.h"

class Monster
{
private:
    Monster() = default;

public:
    static Monster Snail();

    int getForce();

    int loot;
    int coins;
    int damage;
    int combatPower;
};

class EncounterEvent : Event
{
private:
    Monster monster;
};

#endif //TECHNION_234124_ENCOUNTEREVENT_H
