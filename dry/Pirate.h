
#pragma once

#include <iostream>

using std::string;

class Pirate {
private:
    string name;

public:
    Pirate(const string& name);

    ~Pirate() = default;

    void setName(const string& name);

    string getName();

    friend std::ostream &operator<<(std::ostream &os, const Pirate &pirate);
};
