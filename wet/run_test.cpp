#include "Matrix.h"
#include <vector>
#include <iostream>

using std::vector;

int main() {

    vector<vector<int>> data{
            {1, 3},
            {5, 2},
            {6, 3}
    };

    Matrix mat(data.size(), data.front().size());

    for (size_t i = 0; i < data.size(); i++) {
        for (size_t j = 0; j < data[i].size(); j++) {
            mat(i, j) = data[i][j];
        }
    }


    std::cout << mat.rotateCounterClockwise() << std::endl;

    return 0;
}