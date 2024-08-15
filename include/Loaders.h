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

    std::vector<std::string> split(const std::string &s) {
        std::vector<std::string> result;
        std::stringstream ss(s);
        std::string item;

        while (getline(ss, item, ' ')) {
            result.push_back(item);
        }

        return result;
    }


    shared_ptr<Event> createEvent(const string &line) {


        vector<string> lines = split(line);

        if (lines.empty()) {
            throw std::invalid_argument("");
        }

        string key = lines[0];

//        lines.erase(lines.begin());

        // forward the creation to the type info.
        return Event::createType(key, lines);
    }

    vector<shared_ptr<Event>> loadEvents(std::istream &eventsStream) {
        vector<shared_ptr<Event>> events;

        readLines(eventsStream, [&events](const string &line) {
            events.emplace_back(
                    createEvent(line)
            );
        });

        return events;
    }

    vector<shared_ptr<Player>> loadPlayers(std::istream &playersStream) {
        vector<shared_ptr<Player>> players;
        readLines(playersStream, [&players](const string &line) {
            vector<string> playerInfo = split(line);
            players.emplace_back(
                    Player::createType(playerInfo[1], playerInfo)
            );
        });
        return players;
    }


}

#endif //TECHNION_234124_LOADERS_H
