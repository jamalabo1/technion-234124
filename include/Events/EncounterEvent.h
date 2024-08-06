//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_ENCOUNTEREVENT_H
#define TECHNION_234124_ENCOUNTEREVENT_H

#include "Event.h"
#include <map>
#include <memory>
#include <vector>

class Monster {
private:

    string key;
    int loot;
    int damage;
    int combatPower;


protected:
    Monster(string key, int loot, int damage, int combatPower);
    // only allow pack to create a copy.
    Monster(const Monster &, int length);


    string generalStats() const;

public:
    using ptr = std::shared_ptr<const Monster>;
    // disable copies.
    Monster(const Monster &) = delete;


    static std::map<string, ptr> getMonsters();


    int getCombatPower() const;

    int getDamage() const;

    int getLoot() const;

    string getKey() const;

    virtual string getDescription() const;

};

class Pack : public  Monster {
private:
    int length;

public:
    Pack(const std::vector<std::shared_ptr<const Monster>>& pack);

    string getDescription() const override;
};

class EncounterEvent : public  Event {
private:
    // since it's a statically initialized instances, there is no need to copy.
    Monster::ptr monster;

public:
    EncounterEvent(Monster::ptr monster);

    string getDescription() const override;

    string applyTo(std::shared_ptr<Player> player) override;
};

#endif //TECHNION_234124_ENCOUNTEREVENT_H
