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


string SolarEclipseEvent::applyTo(shared_ptr<Player> player) {
    return getSolarEclipseMessage(*player, player->experienceSolarEclipse());
}

SolarEclipseEvent::SolarEclipseEvent() : SpecialEvent("SolarEclipse") {

}

string PotionsMerchantEvent::applyTo(shared_ptr<Player> player) {
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

IMPLEMENT_FACTORY_REGISTER(SpecialEvent) {
    registerFactory("PotionsMerchant", FactorableTypeInfo([](const vector<string> &) {
        return make_shared<PotionsMerchantEvent>();
    }));

    registerFactory("SolarEclipse", FactorableTypeInfo([](const vector<string> &) {
        return make_shared<SolarEclipseEvent>();
    }));
}
