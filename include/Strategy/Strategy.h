//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_BEHAVIOUR_H
#define TECHNION_234124_BEHAVIOUR_H


#include <string>
#include "Factory.h"

using std::string;
using std::make_shared;
using std::make_tuple;
using std::vector;

// forward declaration of player since both depend on each other.
class Player;


#define GENERIC_STRATEGY_REGISTER(Type) IMPLEMENT_FACTORY_REGISTER(Type) { \
        registerFactory(#Type, FactorableTypeInfo([](const vector<string> &) {\
            return make_tuple(make_shared<Type>(), 1);\
        }));\
}\

// it's all about handling types of events
// meaning that its jawhar is the handling.
class Strategy : public Factorable<Strategy> {
protected:
    // prevent creating a base type instance.
    // although since this is ab abstract class, this method is useless.
    Strategy() = default;

public:
    virtual ~Strategy() = default;

    virtual int buyHp(Player &, const int &cost, const int &hp) = 0;

    virtual string getKey() = 0;
};

#endif //TECHNION_234124_BEHAVIOUR_H
