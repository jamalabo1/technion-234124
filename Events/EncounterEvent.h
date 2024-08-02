//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_ENCOUNTEREVENT_H
#define TECHNION_234124_ENCOUNTEREVENT_H

#include "Event.h"

class EncounterEvent : public Event {
protected:
    string MonsterName;
    int CombatPower;
    int Loot;
    int Damage;

public:
    EncounterEvent(const string &name, int combatPower, int loot, int damage)
        : CombatPower(combatPower), Loot(loot), Damage(damage) {}

    // will be overridden by monster types
    virtual int getCombatPower() const {return CombatPower; }
    virtual int getLoot() const { return Loot; }
    virtual int getDamage() const { return Damage; }

    virtual ~EncounterEvent() = default;
};

class Snail : EncounterEvent{
public:
    // with the base constructor initialising with the snail values
    Snail() : EncounterEvent("Snail", 5 , 2, 10) {}
};

class Slime : EncounterEvent{
public:
    // with the base constructor initialising with the Slime values
    Slime() : EncounterEvent("Slime", 12 , 5, 25) {}
};

class Balrog : EncounterEvent{
public:
    // with the base constructor initialising with the snail values
    Balrog() : EncounterEvent("Balrog", 15 , 100, 9001) {}

    void increaseCombatPower() {
        CombatPower += 2; // after each counter
    }
};

#endif //TECHNION_234124_ENCOUNTEREVENT_H
