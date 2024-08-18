//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_ARCHER_H
#define TECHNION_234124_ARCHER_H

#include "Player.h"

class Archer : public Player {
private:
    CREATE_FACTORY_REGISTER();
public:
    Archer(string name, shared_ptr<Strategy> strategy);

    static inline string Key = "Archer";
};

#endif //TECHNION_234124_ARCHER_H
