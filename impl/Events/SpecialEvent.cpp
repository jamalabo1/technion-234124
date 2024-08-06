//
// Created by jamal on 04/08/2024.
//
#include "Events/SpecialEvent.h"
#include "../../Utilities.h"

SpecialEvent::SpecialEvent(const string &key) : key(key) {

}

string SpecialEvent::getDescription() const {
    return key;
}


string SolarEclipseEvent::applyTo(std::shared_ptr<Player> player) {
    return getSolarEclipseMessage(*player, player->experienceSolarEclipse());
}

SolarEclipseEvent::SolarEclipseEvent() : SpecialEvent("SolarEclipse") {

}

string PotionsMerchantEvent::applyTo(std::shared_ptr<Player> player) {
    return getPotionsPurchaseMessage(*player, player->reviewOffer(offer.getCost(), offer.getHp()));
}

PotionsMerchantEvent::PotionsMerchantEvent() : SpecialEvent("PotionsMerchant"), offer(5, 10) {

}

PotionsMerchantEvent::PotionsMerchantOffer::PotionsMerchantOffer(const int cost, const int hp) : cost(cost), hp(hp) {

}

int PotionsMerchantEvent::PotionsMerchantOffer::getCost() const {
    return cost;
}

int PotionsMerchantEvent::PotionsMerchantOffer::getHp() const {
    return hp;
}

