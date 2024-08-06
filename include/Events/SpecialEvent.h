//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_SPECIALEVENT_H
#define TECHNION_234124_SPECIALEVENT_H

#include "Event.h"


class SpecialEvent : public  Event {
private:
    string key;
protected:
    SpecialEvent(const string &key);

public:

    string getDescription() const override;
};


class SolarEclipseEvent : public  SpecialEvent {
public:
    SolarEclipseEvent();

    string applyTo(std::shared_ptr<Player> player) override;
};


class PotionsMerchantEvent : public  SpecialEvent {
private:
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
    PotionsMerchantEvent();

    string applyTo(std::shared_ptr<Player> player) override;
};

#endif //TECHNION_234124_SPECIALEVENT_H
