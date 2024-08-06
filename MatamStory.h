#pragma once

#include <iostream>
#include <vector>

#include "Players/Player.h"
#include "Events/Event.h"


class MatamStory
{
private:
    unsigned int m_turnIndex;


    std::vector<std::shared_ptr<Event>> events;
    std::vector<std::shared_ptr<Player>> players;

    void postEvent(const Player &);


    /**
     * Playes a single turn for a player
     *
     * @param player - the player to play the turn for
     *
     * @return - void
    */
    void playTurn(std::shared_ptr<Player> player);

    /**
     * Plays a single round of the game
     *
     * @return - void
    */
    void playRound();

    /**
     * Checks if the game is over
     *
     * @return - true if the game is over, false otherwise
    */
    bool isGameOver() const;


    void printLeaderboard();

public:
    /**
     * Constructor of MatamStory class
     *
     * @param eventsStream - events input stream (file)
     * @param playersStream - players input stream (file)
     *
     * @return - MatamStory object with the given events and players
     *
    */
    MatamStory(std::istream& eventsStream, std::istream& playersStream);

    /**
     * Plays the entire game
     *
     * @return - void
    */
    void play();
};
