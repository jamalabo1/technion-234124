//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_SPECIALEVENT_H
#define TECHNION_234124_SPECIALEVENT_H

#include "Event.h"


class SpecialEvent : Event
{
};

class PotionsMerchantOffer
{
public:
    int cost;
    int hp;
};

class PotionsMerchantEvent : SpecialEvent
{
private:
    PotionsMerchantOffer offer;

public:
    void applyTo(Player& player)
    {
        player.reviewOffer(offer.cost, offer.hp);
    }
};

#endif //TECHNION_234124_SPECIALEVENT_H
