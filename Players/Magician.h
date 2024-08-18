//
// Created by jamal on 01/08/2024.
//

#ifndef TECHNION_234124_MAGICIAN_H
#define TECHNION_234124_MAGICIAN_H

#include "Player.h"


class Magician : public Player {
private:
    CREATE_FACTORY_REGISTER();
public:
    Magician(string name, shared_ptr<Strategy>);

    int experienceSolarEclipse() override;

    static inline string Key = "Magician";
};

#endif //TECHNION_234124_MAGICIAN_H
