#include <algorithm>
#include "MatamStory.h"

#include "Utilities.h"
#include "Loaders.h"
#include <functional>

#include <Events/SpecialEvent.h>
#include <Events/EncounterEvent.h>

#include <Strategy/Responsible.h>
#include <Strategy/RiskTaking.h>

#include <Players/Warrior.h>
#include <Players/Magician.h>
#include <Players/Archer.h>

#include <sstream>

using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::make_unique;

// helper operator for shared_ptr<Player>
inline bool operator<(const shared_ptr<Player> &a, const shared_ptr<Player> &b) {
    return a->stats() > b->stats();
}

MatamStory::MatamStory(std::istream &eventsStream, std::istream &playersStream) {
    this->events = Loaders::loadEvents(eventsStream);

    this->players= Loaders::loadPlayers(playersStream);

    this->m_turnIndex = 0;
}

void MatamStory::playTurn(shared_ptr<Player> player) {
    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Get the next event from the events list
     * 2. Print the turn details with "printTurnDetails"
     * 3. Play the event
     * 4. Print the turn outcome with "printTurnOutcome"
    */
    shared_ptr<Event> currentEvent = events[m_turnIndex % events.size()];

    printTurnDetails(m_turnIndex + 1, *player, *currentEvent);

    string result = currentEvent->applyTo(player);

    printTurnOutcome(result);

    postEvent(*player);
}

void MatamStory::playRound() {

    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/

    for (shared_ptr<Player> &player: players) {
        if (player->getHealthPoints() == 0)continue;
        playTurn(player);
    }

    /*=============================================*/

    printRoundEnd();

    printLeaderboard();
    /*=======================================================================================*/

    printBarrier();
}

bool MatamStory::isGameOver() const {
    /*===== TODO: Implement the game over condition =====*/

    bool all_dead = true;
    for (const auto &item: players) {
        if (item->getLevel() == 10) return true;
        if (item->getHealthPoints() != 0) {
            all_dead = false;
        }
    }
    return all_dead;

    // if players is empty then all players are 0 health.
    return players.empty() || std::any_of(players.begin(), players.end(),
                                          [](const shared_ptr<Player> &player) {
                                              return player->getLevel() == 10;
                                          }
    ); // Replace this line
    /*===================================================*/
}

void MatamStory::play() {
    printStartMessage();
    /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/

    for (int i = 0; i < (int) players.size(); ++i) {
        printStartPlayerEntry(i + 1, *players[i]);
    }

    /*=========================================================================================*/
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/
    auto maxPlayer = *std::min_element(players.begin(), players.end());
    if (maxPlayer->getHealthPoints() == 0) {
        printNoWinners();
    } else {
        printWinner(*maxPlayer);
    }

    /*========================================================================*/
}

void MatamStory::postEvent(const Player &player) {
    m_turnIndex = (m_turnIndex + 1);
}


void MatamStory::printLeaderboard() {
    printLeaderBoardMessage();

    /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/

    vector<shared_ptr<Player>> sorted(players.size());

    std::partial_sort_copy(players.begin(), players.end(), sorted.begin(), sorted.end());


    for (size_t i = 0; i < sorted.size(); i++) {
        printLeaderBoardEntry(i + 1, *sorted[i]);
    }
}
