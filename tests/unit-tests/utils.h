//
// Created by jamal on 09/07/2024.
//

#ifndef HW2_UTILS_H
#define HW2_UTILS_H

#include <tuple>
#include <vector>

namespace testUtils {
    using Dim = std::tuple<int, int>;

    std::vector<Dim> generateRandomDims(int len);

    int generateRandomNumber(int start, int end);
}

#endif //HW2_UTILS_H
