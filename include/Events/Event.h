#pragma once

#include <string>
#include <Players/Player.h>

using std::string;

class Event
{
public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    string getDescription() const;

    void applyTo(Player& player);
};
