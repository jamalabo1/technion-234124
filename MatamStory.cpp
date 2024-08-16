#include <algorithm>
#include "MatamStory.h"

#include "Utilities.h"
#include "Loaders.h"

#include <functional>

#include <sstream>


using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::make_unique;

// helper operator for shared_ptr<Player>
inline bool operator<(const shared_ptr<Player> &a, const shared_ptr<Player> &b) {
    if (a->stats() == b->stats()) {
        return a->getName() < b->getName();
    }
    return a->stats() > b->stats();
}


MatamStory::MatamStory(std::istream &eventsStream, std::istream &playersStream) {
    try {
        this->events = Loaders::loadEvents(eventsStream);

        if (events.size() < 2) {
            throw std::invalid_argument("");
        }

    } catch (const std::invalid_argument &) {

        std::cout << "Invalid Events File" << std::endl;
        exit(1);
    }

    try {
        this->players = Loaders::loadPlayers(playersStream);

        if (players.size() < 2) {
            throw std::invalid_argument("");
        }

    } catch (const std::invalid_argument &) {
        std::cout << "Invalid Players File" << std::endl;
        exit(1);
    }

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
    // get the current event based on a modules index.
    shared_ptr<Event> currentEvent = events[m_turnIndex % events.size()];

    // print the details of the current player & event
    printTurnDetails(m_turnIndex + 1, *player, *currentEvent);

    // apply the event to the player and get the result.
    string result = currentEvent->applyTo(player);

    // print the outcome of the event.
    printTurnOutcome(result);

    // perform post action after an event has been applied.
    postEvent();
}

void MatamStory::playRound() {

    // print round start message
    printRoundStart();

    // loop over players and play turns.
    for (shared_ptr<Player> &player: players) {
        // if player has been terminated, do not include!.
        if (player->getHealthPoints() == 0)continue;
        playTurn(player);
    }

    // print round end message
    printRoundEnd();

    // print the leaderboard after playing a round
    printLeaderboard();

    printBarrier();
}

bool MatamStory::isGameOver() const {
    // check if all players are dead or there is a winner.
    bool all_dead = true;
    for (const auto &item: players) {
        if (item->getLevel() == WIN_LEVEL) return true;
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

    for (int i = 0; i < (int) players.size(); ++i) {
        printStartPlayerEntry(i + 1, *players[i]);
    }

    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();

    // if there is no players, then there is no winners.
    if (players.empty()) {
        printNoWinners();
        return;
    }

    auto maxPlayer = *std::min_element(players.begin(), players.end());
    if (maxPlayer->getHealthPoints() == 0) {
        printNoWinners();
    } else {
        printWinner(*maxPlayer);
    }
}

void MatamStory::postEvent() {
    m_turnIndex = (m_turnIndex + 1);
}


void MatamStory::printLeaderboard() {
    printLeaderBoardMessage();

    vector<shared_ptr<Player>> sorted(players.size());

    std::partial_sort_copy(players.begin(), players.end(), sorted.begin(), sorted.end());


    for (size_t i = 0; i < sorted.size(); i++) {
        printLeaderBoardEntry(i + 1, *sorted[i]);
    }
}
