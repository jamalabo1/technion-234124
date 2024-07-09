//
// Created by jamal on 09/07/2024.
//

#include "MatrixTestBase.h"

using std::tuple;
using std::vector;
using testUtils::generateRandomNumber;

tuple<Matrix, vector<vector<int>>> MatrixTestBase::generateMatrix(int rows, int cols) {
    vector<vector<int>> matData;
    matData.reserve(rows);
    Matrix mat(rows, cols);

    for (int i = 0; i < rows; i++) {
        vector<int> row;
        for (int j = 0; j < cols; j++) {
            int n = generateRandomNumber(-50, 50);
            mat(i, j) = n;
            row.push_back(n);
        }
        matData.push_back(row);
    }
    return {mat, matData};
}

Matrix MatrixTestBase::generateHelperMatrix(int rows, int cols) {
    auto [mat, _] = generateMatrix(rows, cols);
    return mat;
}