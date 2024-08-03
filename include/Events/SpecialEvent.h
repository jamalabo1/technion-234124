//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_SPECIALEVENT_H
#define TECHNION_234124_SPECIALEVENT_H

#include "Event.h"


class SpecialEvent : Event {
};


class SolarEclipseEvent : SpecialEvent {
public:
    void applyTo(Player &player) override;
};


class PotionsMerchantEvent : SpecialEvent {
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

    PotionsMerchantEvent();


public:
    void applyTo(Player &player) override;
};

#endif //TECHNION_234124_SPECIALEVENT_H
