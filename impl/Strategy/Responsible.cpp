//
// Created by jamal on 03/08/2024.
//
#include <Players/Player.h>
#include <Strategy/Responsible.h>

Responsible::Responsible() = default;

void Responsible::buyHp(Player& player, const int& cost, const int& hp)
{
    while (player.getCoins() > cost || player.isFullHealth())
    {
        player.trade(cost, hp);
    }
};
