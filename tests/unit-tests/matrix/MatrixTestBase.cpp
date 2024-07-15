//
// Created by jamal on 09/07/2024.
//

#include "MatrixTestBase.h"

using std::tuple;
using std::vector;
using testUtils::generateRandomNumber;

tuple<Matrix, vector<vector<int>>> MatrixTestBase::generateMatrix(int rows, int cols) {
    return testUtils::generateMatrix(rows, cols);
}

Matrix MatrixTestBase::generateHelperMatrix(int rows, int cols) {
    auto [mat, _] = generateMatrix(rows, cols);
    return mat;
}