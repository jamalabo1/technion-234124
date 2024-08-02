#ifndef TECHNION_234124_PLAYER_H
#define TECHNION_234124_PLAYER_H

#include <memory>
#include <string>
#include <Strategy/Strategy.h>

using std::string;
using std::unique_ptr;

class Player
{
private:
    string name;
    int level;
    int force;
    int health;
    int maxHealth;
    int coins;
    unique_ptr<Strategy> strategy;

protected:
    ~Player() = default;


    explicit Player(unique_ptr<Strategy>& strategy, const int level = 1, const int coins = 10,
                    const int force = 5,
                    const int health = 100) :
        level(level), force(force), health(health), maxHealth(health), coins(coins), strategy(std::move(strategy))
    {
    }

    void setMaxHealth(int maxHealth);

    void setCoins(int coins);

public:
    /**
     * Gets the description of the player
     *
     * @return - description of the player
    */
    string getDescription() const;

    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    string getName() const;

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    int getLevel() const;

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    int getForce() const;

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    int getHealthPoints() const;

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    int getCoins() const;

    /**
     * Gets the combat power of player.
     *
     * @return - combat power of player
     */
    virtual int getCombatPower() const;

    /**
    * Checks wether player is at max health.
    *
    * @return - true if player at max health
    */
    virtual bool isFullHealth() const;


    /**
     *  a function called after the player had a battel
     * @param battelWon describes wether the player has won the battel
     */
    void virtual postCombat(bool battelWon);


    /**
     * levels up the player
     * @return newly set level
     */
    int levelUp(int step = 1);

    /**
     *
     * @return newly set hp
     */
    int loseHp(int hp);

    int loseCoins(int coins);

    /**
     *
     * @param hp Hp amount to add
     * @return health of player after add
     */
    int addHp(int hp);


    /**
     *
     * @return newly set conins
     */
    int addCoins(int quantity);

    /**
     * offers the player to review an offer from the merchant

     * @param cost Cost of the hp offer
     * @param hp hp offer
     */
    void reviewOffer(int cost, int hp);

    /**
     * Performs a trade of hp for coins
     * @param cost cost of the trade
     * @param hp hp trade
     */
    void trade(int cost, int hp);
};
#endif //TECHNION_234124_PLAYER_H
