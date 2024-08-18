//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_SPECIALEVENT_H
#define TECHNION_234124_SPECIALEVENT_H

#include "Event.h"

using std::vector;
using std::shared_ptr;
using std::string;
using std::make_tuple;

#define GENERIC_SPECIAL_EVENT_REGISTER(Type)  \
IMPLEMENT_FACTORY_REGISTER(Type) { \
        Type::registerFactory(#Type, FactorableTypeInfo([](const vector<string> &) { \
                return make_tuple(make_shared<Type>(), 1); \
        })); \
}

class SpecialEvent : public Event {
private:
    string key;

protected:
    explicit SpecialEvent(const string &key);

public:

    string getDescription() const override;
};


class SolarEclipse : public SpecialEvent {
private:
    CREATE_FACTORY_REGISTER();
public:
    SolarEclipse();

    string applyTo(shared_ptr<Player> player) override;
};


class PotionsMerchant : public SpecialEvent {
private:
    CREATE_FACTORY_REGISTER();
private:
    static const int DEFAULT_OFFER_COST = 5;
    static const int DEFAULT_OFFER_HP = 10;

    class PotionsMerchantOffer {


        int cost;
        int hp;
    public:

        PotionsMerchantOffer(int cost, int hp);

        int getCost() const;

        int getHp() const;

    };

    PotionsMerchantOffer offer;

public:
    PotionsMerchant();

    string applyTo(shared_ptr<Player> player) override;
};

#endif //TECHNION_234124_SPECIALEVENT_H