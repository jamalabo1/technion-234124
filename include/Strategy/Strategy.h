//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_BEHAVIOUR_H
#define TECHNION_234124_BEHAVIOUR_H


#include <string>

// forward declaration of player since both depend on each other.
class Player;

// it's all about handling types of events
// meaning that its jawhar is the handling.
class Strategy {
protected:
    // prevent creating a base type instance.
    // although since this is ab abstract class, this method is usless.
    Strategy() = default;

public:
    virtual ~Strategy() = default;

    virtual int buyHp(Player &, const int &cost, const int &hp) = 0;

    virtual std::string getKey() = 0;
};

#endif //TECHNION_234124_BEHAVIOUR_H
