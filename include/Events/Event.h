#pragma once

#include <string>
#include <Players/Player.h>

using std::string;

class Event {
protected:
    // prevent creating a base type instance.
    Event() = default;

public:
    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    virtual string getDescription() const = 0;

    virtual string applyTo(std::shared_ptr<Player> player) = 0;
};
