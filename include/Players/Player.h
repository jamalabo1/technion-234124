#ifndef TECHNION_234124_PLAYER_H
#define TECHNION_234124_PLAYER_H

#include <memory>
#include <string>
#include <Strategy/Strategy.h>
#include "Factory.h"


using std::string;
using std::unique_ptr;
using std::shared_ptr;

#define GENERIC_REGISTER(Type) IMPLEMENT_FACTORY_REGISTER(Type) { \
        registerFactory(#Type, FactorableTypeInfo([](const std::vector<std::string> &arguments) {\
            auto strategy = Strategy::createType(arguments[2], arguments);\
            return std::make_shared<Type>(arguments[0], strategy);\
        }));\
}\


class Player : public Factorable<Player> {
private:
    string name;
    int level;
    int force;
    int health;
    int maxHealth;
    int coins;
    shared_ptr<Strategy> strategy;

    string character;

protected:
    explicit Player(string name,
                    shared_ptr<Strategy> &strategy,
                    string job,
                    int level = 1,
                    int coins = 10,
                    int force = 5,
                    int health = 100);

    void setMaxHealth(int healthQty);

    void setHealth(int healthQty);

    void setCoins(int numOfCoins);

public:
    // prevent creating a base type instance.
    Player() = delete;

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
    *  a function called after the player had a battle
    * @param battleWon describes weather the player has won the battle
    */
    virtual void postCombat(bool battleWon);


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

    /**
     *
     * @return newly set coins
     */
    int loseCoins(int coins);

    /**
     *
     * @param hp Hp amount to add
     * @return health of player after add
     */
    int addHp(int hp);


    /**
     *
     * @return newly set coins
     */
    int addCoins(int quantity);

    /**
     * offers the player to review an offer from the merchant

     * @param cost Cost of the hp offer
     * @param hp hp offer
     */
    int reviewOffer(int cost, int hp);

    /**
     * Performs a trade of hp for coins
     * @param cost cost of the trade
     * @param hp hp trade
     */
    void trade(int cost, int hp);


    int addForce(int quantity);

    int loseForce(int quantity);


    /**
     * Player experiences a solar eclipse.
     * */
    virtual int experienceSolarEclipse();

    std::tuple<int, int, string> stats() const;
};

#endif //TECHNION_234124_PLAYER_H
