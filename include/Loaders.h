//
// Created by jamal on 07/08/2024.
//

#ifndef TECHNION_234124_LOADERS_H
#define TECHNION_234124_LOADERS_H

#include <vector>

#include <Events/Event.h>
#include <Strategy/Strategy.h>
#include <Players/Player.h>

#include <Events/SpecialEvent.h>
#include <Events/EncounterEvent.h>
//
#include <Strategy/Responsible.h>
#include <Strategy/RiskTaking.h>
//
#include <Players/Warrior.h>
#include <Players/Magician.h>
#include <Players/Archer.h>

#include "Factory.h"

#include <stdexcept>
#include <sstream>

namespace Loaders {

    using std::shared_ptr;
    using std::vector;

    void readLines(std::istream &stream, const std::function<void(string &)> &callback) {
        std::string line;
        while (getline(stream, line)) {
            callback(line);
        }
    }

    vector<string> split(const string &s) {
        vector<string> result;
        string item(s);
        item += " ";

        int startIndex = 0;
        int endIndex = 0;
        for (size_t i = 0; i < item.size(); i++) {
            if (item[i] == ' ') {
                if (startIndex < endIndex) {
                    result.emplace_back(
                            s.substr(startIndex, (endIndex - startIndex))
                    );
                }
                startIndex = i + 1;
                endIndex = i + 1;
            } else {
                endIndex++;
            }
        }

        return result;
    }


    void createEvent(vector<shared_ptr<Event>> &events, const string &line) {
        vector<string> arguments = split(line);
        for (size_t i = 0; i < arguments.size(); i++) {
            vector<string> subArguments{arguments.begin() + i, arguments.end()};
            auto [event, length] = Event::createType(subArguments[0], subArguments);
            events.emplace_back(
                    event
            );
            i += (length - 1);
        }
    }

    vector<shared_ptr<Event>> loadEvents(std::istream &eventsStream) {
        vector<shared_ptr<Event>> events;

        readLines(eventsStream, [&events](const string &line) {
            createEvent(events, line);
        });

        return events;
    }

    vector<shared_ptr<Player>> loadPlayers(std::istream &playersStream) {
        vector<shared_ptr<Player>> players;
        readLines(playersStream, [&players](const string &line) {
            vector<string> arguments = split(line);

            for (size_t i = 0; i < arguments.size(); i++) {

                vector<string> playerInfo{arguments.begin() + i, arguments.end()};
                if (playerInfo.size() < 3) {
                    throw std::invalid_argument("invalid player info size");
                }

                auto [player, length] = Player::createType(playerInfo[1], playerInfo);

                players.emplace_back(
                        player
                );
                i += (length - 1);
            }
        });
        return players;
    }


}

#endif //TECHNION_234124_LOADERS_H
