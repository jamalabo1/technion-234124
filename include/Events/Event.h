#pragma once

#include <string>
#include <vector>
#include <map>

#include <Players/Player.h>
#include <functional>
#include <stdexcept>

using std::string;


class Event : public Factorable<Event> {
//protected:
//    class EventTypeInfo {
//    public:
//        using FactoryArgType = std::vector<string>;
//        using FactoryRType = std::shared_ptr<Event>;
//        using FactoryType = std::function<FactoryRType(FactoryArgType)>;
//
//        EventTypeInfo() = default;
//
//        EventTypeInfo(const FactoryType &factory) : factory(factory) {};
//
//        FactoryType factory;
//    };
//
//private:
//    static inline std::map<string, EventTypeInfo> events;
//
//protected:
//    // prevent creating a base type instance.
//    Event() = default;
//
//    static void registerEventFactory(const string &, const EventTypeInfo &);

public:

//    class EventDoesNotExistException : public std::exception {
//
//    public:
//        EventDoesNotExistException() : std::exception("event does not exist") {}
//    };

//    static EventTypeInfo::FactoryRType createEvent(const string &key, const EventTypeInfo::FactoryArgType &arguments);

    /**
     * Gets the description of the event
     *
     * @return - the description of the event
    */
    virtual string getDescription() const = 0;

    virtual string applyTo(std::shared_ptr<Player> player) = 0;
};



