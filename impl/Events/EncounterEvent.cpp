//
// Created by jamal on 03/08/2024.
//
#include <Events/EncounterEvent.h>

#include <utility>


Monster::Monster(string  key, int loot, int damage, int combatPower) : key(key), loot(loot), damage(damage),
                                                                      combatPower(combatPower) {


}


std::vector<std::tuple<string, Monster>> Monster::getMonsters() {
    static Monster snail("Snail", 5, 5, 5);
    static Monster slime("Slime", 5, 5, 5);
    static Monster barlog("Barlog", 5, 5, 5);

    return {
            {snail.getKey(),  snail},
            {slime.getKey(),  slime},
            {barlog.getKey(), barlog}
    };
}


void EncounterEvent::applyTo(Player &player) {
    const bool playerWon = player.getCombatPower() >= monster.getCombatPower();

    if (playerWon) {
        player.levelUp();
        player.addCoins(monster.getLoot());
    } else {
        player.loseHp(monster.getDamage());
    }
    player.postCombat(playerWon);
}
