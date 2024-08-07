//
// Created by jamal on 02/08/2024.
//

#include "Players/Player.h"

Player::Player(string name, shared_ptr<Strategy> &strategy, string job, const int level, const int coins,
               const int force, const int health) : name(name),
                                                    level(level), force(force), health(health), maxHealth(health),
                                                    coins(coins), strategy(std::move(strategy)), character(job) {
}


void Player::setMaxHealth(const int healthQty) {
    maxHealth = healthQty;
}

void Player::setHealth(int healthQty) {
    health = healthQty;
}


void Player::setCoins(const int numOfCoins) {
    coins = numOfCoins;
}

string Player::getDescription() const {
    return getName() + ", " + character + " with " + strategy->getKey() + " character" +
           " (level " + std::to_string(getLevel()) + ", force " + std::to_string(getForce()) + ")";
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
    return addHp(-hp);
}

int Player::loseCoins(const int coinsNum) {
    return coins -= coinsNum;
}


int Player::addHp(const int hp) {
    health = std::min(maxHealth, std::max(health + hp, 0));
    return health;
}

int Player::addCoins(const int quantity) {
    return coins += quantity;
}

int Player::reviewOffer(const int cost, const int hp) {
    return strategy->buyHp(*this, cost, hp);
}

void Player::trade(const int cost, const int hp) {
    loseCoins(cost);

    addHp(hp);
}

int Player::experienceSolarEclipse() {
    loseForce(1);
    return -1;
}

std::tuple<int, int, string> Player::stats() const {
    return std::tie(level, coins, name);
}

int Player::addForce(int quantity) {
    return force += quantity;
}

int Player::loseForce(int quantity) {
    return addForce(-quantity);
}


