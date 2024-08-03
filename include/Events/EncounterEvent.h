//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_ENCOUNTEREVENT_H
#define TECHNION_234124_ENCOUNTEREVENT_H

#include "Event.h"
#include <vector>

class Monster {
private:

    string key;
    int loot;
    int damage;
    int combatPower;

    Monster() = delete;

    Monster(string  key, int loot, int damage, int combatPower);

public:



    static std::vector<std::tuple<string, Monster>> getMonsters() ;

    int getCombatPower();
    int getDamage();
    int getLoot();

    string getKey()const;
};

class EncounterEvent : Event {
private:
    Monster monster;

public:
    EncounterEvent(Monster monster);

    void applyTo(Player &player) override;
};

#endif //TECHNION_234124_ENCOUNTEREVENT_H
