//
// Created by jamal on 03/08/2024.
//
#include <Players/Player.h>
#include <Strategy/RiskTaking.h>

RiskTaking::RiskTaking() = default;

int RiskTaking::buyHp(Player &player, const int &cost, const int &hp) {
    if (player.getHealthPoints() < 50) {
        player.trade(cost, hp);
        return cost;
    }
    return 0;
}

std::string RiskTaking::getKey() {
    return "RiskTaking";
}

GENERIC_STRATEGY_REGISTER(RiskTaking);
