//
// Created by jamal on 03/08/2024.
//

#ifndef RESPONSIBILE_H
#define RESPONSIBILE_H

#include "Strategy.h"

class Responsible : public Strategy
{
public:
    Responsible();

    int buyHp(Player& player, const int& cost, const int& hp) override;

    std::string getKey() override;
};

#endif //RESPONSIBILE_H
