
#include "Pirate.h"


Pirate::Pirate(const string& name): name(name) {}


void Pirate::setName(const string& name){
    this->name = name;
}


std::string Pirate::getName(){
    return name;
}


std::ostream &operator<<(std::ostream &os, const Pirate &pirate){
    os << pirate.name;
    return os;
}
