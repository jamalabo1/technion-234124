#pragma once

#include <string>
#include <vector>
#include <map>

#include "../Players/Player.h"
#include <functional>
#include <stdexcept>

using std::string;
using std::shared_ptr;




class Event : public Factorable<Event> {
public:
    virtual ~Event() = default;

    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    virtual string getDescription() const = 0;

    virtual string applyTo(shared_ptr<Player> player) = 0;
};



