//
// Created by jamal on 04/08/2024.
//
#include "Events/SpecialEvent.h"

void SolarEclipseEvent::applyTo(Player &player) {
    player.experienceSolarEclipse();
}

void PotionsMerchantEvent::applyTo(Player &player) {
    player.reviewOffer(offer.getCost(), offer.getHp());
}

PotionsMerchantEvent::PotionsMerchantEvent() : offer(5, 10) {

}

PotionsMerchantEvent::PotionsMerchantOffer::PotionsMerchantOffer(const int cost, const int hp) : cost(cost), hp(hp) {

}

int PotionsMerchantEvent::PotionsMerchantOffer::getCost() const {
    return cost;
}

int PotionsMerchantEvent::PotionsMerchantOffer::getHp() const {
    return hp;
}
