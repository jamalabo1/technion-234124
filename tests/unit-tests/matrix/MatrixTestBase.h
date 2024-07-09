//
// Created by jamal on 09/07/2024.
//

#ifndef HW2_MATRIXTESTBASE_H
#define HW2_MATRIXTESTBASE_H

#include "Matrix.h"
#include <vector>
#include <tuple>
#include <utils.h>

class MatrixTestBase {
public:
    static std::tuple<Matrix, std::vector<std::vector<int>>> generateMatrix(int rows, int cols);
    static Matrix generateHelperMatrix(int rows, int cols);
};

#endif //HW2_MATRIXTESTBASE_H
