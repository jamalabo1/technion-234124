#include <algorithm>
#include "MatamStory.h"

#include "Utilities.h"
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

void readLines(std::istream &stream, const std::function<void(string &)> &callback) {
    std::string line;
    while (getline(stream, line)) {
//        std::stringstream sline(line);
//        std::string platIndependent;
//        sline >> platIndependent;

        callback(line);
    }
}

std::vector<std::string> split(const std::string &s) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;

    while (getline(ss, item, ' ')) {
        result.push_back(item);
    }

    return result;
}

MatamStory::MatamStory(std::istream &eventsStream, std::istream &playersStream) {

    /*===== TODO: Open and read events file =====*/


    const std::map<string, Monster::ptr> &monsters = Monster::getMonsters();


    readLines(eventsStream, [&monsters, this](string &line) {
        // if type is a monster
        if (monsters.count(line)) {
            this->events.emplace_back(
                    make_shared<EncounterEvent>(monsters.at(line))
            );
        } else if (line == "SolarEclipse") {
            this->events.emplace_back(
                    make_shared<SolarEclipseEvent>()
            );
        } else if (line == "PotionsMerchant") {
            this->events.emplace_back(
                    make_shared<PotionsMerchantEvent>()
            );
        } else {
            auto lineSplit = split(line);
            if (lineSplit.size() == 0);// TODO: error;

            if (lineSplit[0] == "Pack") {
                // if size is 1 then there is a problem
                if (lineSplit.size() == 1) {
                    //TODO: error;
                }


                int length = std::atoi(lineSplit[1].c_str());
                vector<Monster::ptr> monsterPack;
                for (int i = 0; i < length; i++) {
                    string monsterKey = lineSplit[2 + i];

                    monsterPack.emplace_back(
                            monsters.at(monsterKey)
                    );
                }
                this->events.emplace_back(
                        make_shared<EncounterEvent>(
                                make_shared<Pack>(monsterPack)
                        )
                );
            } else {
                //TODO: error
            }
            //it;s a pack
        }
    });


    readLines(playersStream, [this](string &line) {

        vector<string> playerInfo = split(line);

        string name = playerInfo[0];
        string job = playerInfo[1];
        string character = playerInfo[2];

        auto strategyFactory = [&character]() -> unique_ptr<Strategy> {
            if (character == "Responsible") {
                return make_unique<Responsible>();
            }
            if (character == "RiskTaking") {
                return make_unique<RiskTaking>();
            }
            return {};
        };

        if (job == "Warrior") {
            this->players.emplace_back(
                    shared_ptr<Player>(new Warrior(name, strategyFactory()))
            );
        } else if (job == "Archer") {
            this->players.emplace_back(
                    shared_ptr<Player>(new Archer(name, strategyFactory()))
            );
        } else if (job == "Magician") {
            this->players.emplace_back(
                    shared_ptr<Player>(new Magician(name, strategyFactory()))
            );
        }

    });
    /*==========================================*/


    /*===== TODO: Open and Read players file =====*/

    /*============================================*/


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

    for (int i = 0; i < players.size(); ++i) {
        printStartPlayerEntry(i + 1, *players[i]);
    }

    /*=========================================================================================*/
    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();
    /*===== TODO: Print either a "winner" message or "no winner" message =====*/
    auto maxPlayer  = *std::min_element(players.begin(), players.end());
    if(maxPlayer->getHealthPoints() == 0) {
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
