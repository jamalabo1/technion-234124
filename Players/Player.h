
#pragma once

#include <string>

using std::string;

class Player {
protected:
    char Name[15];
    int Level = 1;
    int Force = 5;
    int current_HP;
    int max_HP = 100;
    int Coins = 10;
    string Job;
     string Character;
public:
    /**
     * Gets the description of the player
     *
     * @return - description of the player
    */
    string getDescription() const{
        return getName() + ", " + Job + " with" + Character + " character" +
            "(level " + std ::to_string(getLevel()) + ", force " + std::to_string(getForce()) + ")";
    }

    /**
     * Gets the name of the player
     *
     * @return - name of the player
    */
    void setName(char n[]){
        strcpy(Name, n);
    }
    string getName() const{
        return Name;
    }

    /**
     * Gets the current level of the player
     *
     * @return - level of the player
    */
    void setLevel(int m){
        if(m < 1 || m > 10) return;

        Level = m;
    }
    int getLevel() const{
        return Level;
    }

    /**
     * Gets the of force the player has
     *
     * @return - force points of the player
    */
    void setForce(int m){
        if(m < 0) return;
        Force = m;
    }
    int getForce() const{
        return Force;
    }

    /**
     * Gets the amount of health points the player currently has
     *
     * @return - health points of the player
    */
    void setHealthPoints( int m){
        if(m < 0 || m > max_HP) return;
        current_HP = m;
    }
    int getHealthPoints() const{
        return current_HP;
    }

    /**
     * Gets the amount of coins the player has
     *
     * @return - coins of the player
    */
    void setCoins(int m){
        if(m < 0) return;
        Coins = m;
    }
    int getCoins() const{
        return Coins;
    }

    void setJob(const string &job){
        Job = job;
    }

    void setCharacter(const string &character){
        Character = character;
    }

};
