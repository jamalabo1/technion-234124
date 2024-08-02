//
// Created by jamal on 03/08/2024.
//
#include <Events/EncounterEvent.h>

void EncounterEvent::applyTo(Player& player)
{
    const bool playerWon = player.getCombatPower() >= monster.combatPower;

    if (playerWon)
    {
        player.levelUp();
        player.addCoins(monster.coins);
    }
    else
    {
        player.loseHp(monster.damage);
    }
    player.postCombat(playerWon);
}
