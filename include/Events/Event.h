#pragma once

#include <string>
#include <Players/Player.h>

using std::string;

class Event {
public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    string getDescription() const;

    virtual void applyTo(Player &player);
};
