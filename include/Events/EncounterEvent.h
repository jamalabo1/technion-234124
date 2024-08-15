//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_ENCOUNTEREVENT_H
#define TECHNION_234124_ENCOUNTEREVENT_H

#include "Event.h"
#include <memory>
#include <vector>


#define GENERIC_MONSTER_REGISTER(Type) IMPLEMENT_FACTORY_REGISTER(Type) { registerFactory(#Type, \
    FactorableTypeInfo([](const std::vector<string>&){ return std::make_shared<Type>(); })                                                  \
); }

using std::vector;
using std::string;
using std::shared_ptr;

class Monster : public Factorable<Monster> {
private:
    string key;
    int loot;
    int damage;
    int combatPower;


protected:
    Monster(string key, int loot, int damage, int combatPower);


    string generalStats() const;

    void addCombatPower(const int &quantity);

    void setLoot(const int &loot);

    void setCombatPower(const int &combatPower);

    void setDamage(const int &damage);


public:
    // disable copies.
    Monster(const Monster &) = delete;

    virtual ~Monster() = default;


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
    vector<shared_ptr<Monster>> pack;

    CREATE_FACTORY_REGISTER();
public:
    Pack(const vector<shared_ptr<Monster>> &pack);

    string getDescription() const override;

    void postCombat() override;
};


class EncounterEvent : public Event {
private:
    shared_ptr<Monster> monster;

    CREATE_FACTORY_REGISTER();
public:

    EncounterEvent(shared_ptr<Monster> monster);

    string getDescription() const override;

    string applyTo(shared_ptr<Player> player) override;
};

#endif //TECHNION_234124_ENCOUNTEREVENT_H
