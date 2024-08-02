//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_BEHAVIOUR_H
#define TECHNION_234124_BEHAVIOUR_H

class Player;
// it's all about handling types of events
// meaning that its jawhar is the handling.
class Strategy
{
protected:
    Strategy() = default;

public:
    virtual ~Strategy() = default;
    void virtual buyHp(Player&, const int& cost, const int& hp) = 0;
};

#endif //TECHNION_234124_BEHAVIOUR_H
