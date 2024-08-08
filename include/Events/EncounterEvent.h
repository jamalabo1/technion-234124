//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_ENCOUNTEREVENT_H
#define TECHNION_234124_ENCOUNTEREVENT_H

#include "Event.h"
#include <map>
#include <memory>
#include <vector>


#define GENERIC_MONSTER_REGISTER(Type) IMPLEMENT_FACTORY_REGISTER(Type) { registerFactory(#Type, \
    [](const std::vector<string>&){ return std::make_shared<Type>(); }                                                  \
); }

class Monster : public Factorable<Monster> {
protected:

    string key;
    int loot;
    int damage;
    int combatPower;


protected:
    Monster(string key, int loot, int damage, int combatPower);


    string generalStats() const;

public:
    using ptr = std::shared_ptr<const Monster>;

    // disable copies.
    Monster(const Monster &) = delete;


//    static std::map<string, ptr> getMonsters();


    virtual int getCombatPower() const;

    virtual int getDamage() const;

    virtual int getLoot() const;

    string getKey() const;

    virtual void postCombat();

    virtual string getDescription() const;
};

class Snail : public Monster {
private:
    CREATE_FACTORY_REGISTER();
public:
    Snail();
};

class Slime : public Monster {
private:
    CREATE_FACTORY_REGISTER();
public:
    Slime();
};

class Balrog : public Monster {
private:
    CREATE_FACTORY_REGISTER();
public:
    Balrog();

    void postCombat() override;
};

class Pack : public Monster {
private:
    std::vector<shared_ptr<Monster>> pack;

    CREATE_FACTORY_REGISTER();
public:
    Pack(const std::vector<shared_ptr<Monster>> &pack);

    string getDescription() const override;

//    int getLoot() const override;
//
//    int getDamage() const override;
//
//    int getCombatPower() const override;

    void postCombat() override;
};


class EncounterEvent : public Event {
private:
    // since it's a statically initialized instances, there is no need to copy.
    shared_ptr<Monster> monster;

    CREATE_FACTORY_REGISTER();
public:

    EncounterEvent(shared_ptr<Monster> monster);

    string getDescription() const override;

    string applyTo(std::shared_ptr<Player> player) override;
};

#endif //TECHNION_234124_ENCOUNTEREVENT_H
