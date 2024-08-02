//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_SPECIALEVENT_H
#define TECHNION_234124_SPECIALEVENT_H

#include "Event.h"
#include "Player.h"

class SpecialEvent : Event {
protected:
    string EventName;
public:
    SpecialEvent(const string &eventName) : EventName(eventName) {}

    virtual void applyEffect(Player &player) const = 0;

    virtual string getDescription() const override {
        return EventName;
    }
};

class SolarEclipse : SpecialEvent {
public:
    SolarEclipse() : SpecialEvent("SolarEclipse") {}

    virtual void applyEffect(Player &player) const override {
        if(player.getJob() == "Magician"){
            player.setForce(player.getForce() + 1);
        } else {
            player.setForce(player.getForce() - 1);
        }
    }
};

class PotionsMerchant : SpecialEvent {
public:
    PotionsMerchant() : SpecialEvent("PotionsMerchant") {}

    virtual void applyEffect(Player& player) const override {
        int potions  = 0;

        if(player.isResponsible()){
            potions = std::min(player.getCoins()) / 5, (player.getMaxHP() - player.getHealthPoints()) / 10);
        } else if(player.getHealthPoints() < 50){
            potions = 1;
        }

        player.setCoins(player.getCoins() - potions * 5);
        player.setHealthPoints(player.getHealthPoints() + potions * 10);
    }
};

#endif //TECHNION_234124_SPECIALEVENT_H
