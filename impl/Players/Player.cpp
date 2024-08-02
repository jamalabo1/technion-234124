//
// Created by jamal on 02/08/2024.
//

#include "Players/Player.h"


void Player::setMaxHealth(const int maxHealth)
{
    this->maxHealth = maxHealth;
}

void Player::setCoins(const int coins)
{
    this->coins = coins;
}

string Player::getDescription() const
{
    return "desc";
}

string Player::getName() const
{
    return name;
}

int Player::getLevel() const
{
    return level;
}

int Player::getForce() const
{
    return force;
}

int Player::getHealthPoints() const
{
    return health;
}

int Player::getCoins() const
{
    return coins;
}

int Player::getCombatPower() const
{
    return getForce() + getLevel();
}

//  Events are indepedent from the player.
//  They describe their nature, and it's dependent on the player to handle it.
//
void Player::process(const Event& event)
{
}

void Player::postCombat(bool battelWon)
{
}

bool Player::isFullHealth() const
{
    return getHealthPoints() == maxHealth;
}

int Player::levelUp(const int step)
{
    return level += step;
}

int Player::loseHp(const int hp)
{
    return health -= hp;
}

int Player::loseCoins(const int coins)
{
    return this->coins -= coins;
}


int Player::addHp(const int hp)
{
    return health += hp;
}

int Player::addCoins(const int quantity)
{
    return coins += quantity;
}

void Player::reviewOffer(const int cost, const int hp)
{
    strategy.buyHp(*this, cost, hp);
}

void Player::trade(const int cost, const int hp)
{
    loseCoins(cost);

    addHp(hp);
}
