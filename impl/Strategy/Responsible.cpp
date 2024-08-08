//
// Created by jamal on 03/08/2024.
//
#include <Players/Player.h>
#include <Strategy/Responsible.h>

Responsible::Responsible() = default;

int Responsible::buyHp(Player &player, const int &cost, const int &hp) {
    int total = 0;
    while (player.getCoins() > cost || !player.isFullHealth()) {
        player.trade(cost, hp);
        total += hp;
    }
    return total;
}

std::string Responsible::getKey() {
    return "Responsible";
}

GENERIC_STRATEGY_REGISTER(Responsible);