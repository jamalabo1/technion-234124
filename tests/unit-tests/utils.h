//
// Created by jamal on 09/07/2024.
//

#ifndef HW2_UTILS_H
#define HW2_UTILS_H

#include <tuple>
#include <vector>
#include "Matrix.h"

#define EXPECT_MATAM_EQ(value, expr)         std::stringstream out; \
std::stringstream expectedOut;\
out << value;\
expectedOut << expr;\
EXPECT_EQ(out.str(), expectedOut.str())

namespace testUtils {
    using Dim = std::tuple<int, int>;

    std::vector<Dim> generateRandomDims(int len);

    int generateRandomNumber(int start, int end);

    std::tuple<Matrix, std::vector<std::vector<int>>> generateMatrix(int rows, int cols);

}

#endif //HW2_UTILS_H
