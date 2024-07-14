#include <iostream>
#include "Pirate.h"
#include <cstring>

using std::cout, std::endl;


int main() {

    Pirate luffy("Luffy", 1000000, GUM_GUM_FRUIT);
    Pirate zoro("Zoro", 500000);

    const int crewSize = 2;
    
    Pirate strawHatCrew[2] = {luffy, zoro};

    cout << "Straw Hat crew contains:" << endl;
    for (int i = 0; i < crewSize; i++) {
        cout << strawHatCrew[i] << endl;
    }

    return 0;
}
