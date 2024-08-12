//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_RISKTAKING_H
#define TECHNION_234124_RISKTAKING_H

#include "Strategy.h"

class RiskTaking final : public Strategy {
private:
    CREATE_FACTORY_REGISTER();
public:
    RiskTaking();

    int buyHp(Player &player, const int &cost, const int &hp) override;

    string getKey() override;
};

#endif //TECHNION_234124_RISKTAKING_H
