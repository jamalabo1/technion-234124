//
// Created by jamal on 04/08/2024.
//
#include "Events/SpecialEvent.h"
#include "../../Utilities.h"

using std::vector;
using std::shared_ptr;
using std::make_shared;

SpecialEvent::SpecialEvent(const string &key) : key(key) {

}

string SpecialEvent::getDescription() const {
    return key;
}


string SolarEclipse::applyTo(shared_ptr<Player> player) {
    return getSolarEclipseMessage(*player, player->experienceSolarEclipse());
}

SolarEclipse::SolarEclipse() : SpecialEvent("SolarEclipse") {

}

string PotionsMerchant::applyTo(shared_ptr<Player> player) {
    return getPotionsPurchaseMessage(*player, player->reviewOffer(offer.getCost(), offer.getHp()));
}

PotionsMerchant::PotionsMerchant() : SpecialEvent("PotionsMerchant"), offer(DEFAULT_OFFER_COST, DEFAULT_OFFER_HP) {

}

PotionsMerchant::PotionsMerchantOffer::PotionsMerchantOffer(const int cost, const int hp) : cost(cost), hp(hp) {

}

int PotionsMerchant::PotionsMerchantOffer::getCost() const {
    return cost;
}

int PotionsMerchant::PotionsMerchantOffer::getHp() const {
    return hp;
}


GENERIC_SPECIAL_EVENT_REGISTER(PotionsMerchant);
GENERIC_SPECIAL_EVENT_REGISTER(SolarEclipse);