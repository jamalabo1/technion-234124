//
// Created by jamal on 03/08/2024.
//
#include <Players/Player.h>
#include <Strategy/RiskTaking.h>

RiskTaking::RiskTaking() = default;

int RiskTaking::buyHp(Player &player, const int &cost, const int &hp) {
    if (player.getHealthPoints() < MINIMUM_HP) {
        player.trade(cost, hp);
        return 1;
    }
    return 0;
}

std::string RiskTaking::getKey() {
    return "RiskTaking";
}

GENERIC_STRATEGY_REGISTER(RiskTaking);
