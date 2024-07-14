//
// Created by jamal on 09/07/2024.
//

#include "utils.h"

#include <random>


namespace testUtils {

    using std::tuple;
    using std::vector;

    vector<Dim> generateRandomDims(int len) {
        vector<Dim> dims;
        dims.reserve(len);

        for (int i = 0; i < len; i++) {
            dims.emplace_back(generateRandomNumber(1, 50), generateRandomNumber(1, 50));
        }
        return dims;
    }

    int generateRandomNumber(int start, int end) {
        std::random_device rd;
        std::mt19937 rng(rd());
        std::uniform_real_distribution<double> dist(start, end);

        return dist(rng);
    }
}