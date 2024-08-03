//
// Created by jamal on 02/08/2024.
//

#include "Players/Player.h"

Player::Player(unique_ptr<Strategy> &strategy, string job, string character, const int level, const int coins,
               const int force, const int health) :
        level(level), force(force), health(health), maxHealth(health), coins(coins), strategy(std::move(strategy)), job(job), character(character) {
}


void Player::setMaxHealth(const int healthQty) {
    maxHealth = healthQty;
}

void Player::setCoins(const int numOfCoins) {
    coins = numOfCoins;
}

string Player::getDescription() const {
    return getName() + ", " + job + " with" + character + " character" +
           "(level " + std::to_string(getLevel()) + ", force " + std::to_string(getForce()) + ")";
}

string Player::getName() const {
    return name;
}

int Player::getLevel() const {
    return level;
}

int Player::getForce() const {
    return force;
}

int Player::getHealthPoints() const {
    return health;
}

int Player::getCoins() const {
    return coins;
}

int Player::getCombatPower() const {
    return getForce() + getLevel();
}

void Player::postCombat(bool battleWon) {
}

bool Player::isFullHealth() const {
    return getHealthPoints() == maxHealth;
}

int Player::levelUp(const int step) {
    return level += step;
}

int Player::loseHp(const int hp) {
    return health -= hp;
}

int Player::loseCoins(const int coinsNum) {
    return coins -= coinsNum;
}


int Player::addHp(const int hp) {
    return health += hp;
}

int Player::addCoins(const int quantity) {
    return coins += quantity;
}

void Player::reviewOffer(const int cost, const int hp) {
    strategy->buyHp(*this, cost, hp);
}

void Player::trade(const int cost, const int hp) {
    loseCoins(cost);

    addHp(hp);
}

void Player::experienceSolarEclipse() {
    loseHp(1);
}

