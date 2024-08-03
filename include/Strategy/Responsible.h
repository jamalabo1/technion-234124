//
// Created by jamal on 03/08/2024.
//

#ifndef RESPONSIBILE_H
#define RESPONSIBILE_H
#include "Strategy.h"

class Responsible : Strategy
{
public:
    Responsible();

    void buyHp(Player& player, const int& cost, const int& hp) override;
};

#endif //RESPONSIBILE_H
