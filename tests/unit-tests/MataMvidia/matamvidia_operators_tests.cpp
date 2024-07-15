//
// Created by jamal on 15/07/2024.
//

#include <gtest/gtest.h>

#include <MataMvidia.h>
#include <tuple>
#include "utils.h"
#include <iostream>

namespace {

    using std::tuple;
    using std::vector;
    using std::string;

    class MataMvidiaOperatorsFixture
            : public ::testing::TestWithParam<tuple<MataMvidia, vector<Matrix>, vector<Matrix> >> {
    public:
        static vector<ParamType> testValues() {
            vector<ParamType> result;
            int len = testUtils::generateRandomNumber(1, 30);
            for (int i = 0; i < len; i++) {
                auto dims = testUtils::generateRandomDims(10);
                vector<Matrix> matPack;
                vector<Matrix> extraPack;
                for (auto [rows, cols]: dims) {
                    auto [mat, _] = testUtils::generateMatrix(rows, cols);
                    matPack.emplace_back(
                            mat
                    );
                }
                dims = testUtils::generateRandomDims(testUtils::generateRandomNumber(1, 5));
                for (auto [rows, cols]: dims) {
                    auto [extraMat, _] = testUtils::generateMatrix(rows, cols);
                    extraPack.emplace_back(extraMat);
                }

                MataMvidia mataMvidia("authName", "creator", matPack.data(), (int) matPack.size());
                result.emplace_back(mataMvidia, matPack, extraPack);
            }
            return result;
        }
    };

    TEST_P(MataMvidiaOperatorsFixture, MataMvidiaPlusEqMatamOperator_adds_frames) {
        auto [matam, data, extra] = GetParam();

        vector<Matrix> combined(data);

        combined.insert(combined.end(), extra.begin(), extra.end());

        MataMvidia expected("authName", "creator", combined.data(), (int) combined.size());

        MataMvidia right("authName", "creator", extra.data(), (int) extra.size());

        matam += right;

        EXPECT_MATAM_EQ(matam, expected);
    }

    TEST_P(MataMvidiaOperatorsFixture, MataMvidiaPlusEqMatrixOperator_adds_frame) {
        auto [matam, data, extra] = GetParam();

        vector<Matrix> combined(data);

        combined.insert(combined.end(), extra.begin(), extra.begin() + 1);

        MataMvidia expected("authName", "creator", combined.data(), (int) combined.size());

        matam += extra[0];

        EXPECT_MATAM_EQ(matam, expected);
    }


    TEST_P(MataMvidiaOperatorsFixture, MataMvidiaIndexOperator_retuns_correct_frame) {
        auto [matam, data, _] = GetParam();

        for(size_t i=0; i < data.size(); i++) {
            EXPECT_EQ(matam[(int)i], data[i]);
        }
    }

    TEST_P(MataMvidiaOperatorsFixture, MataMvidiaToStringOperator_outs_correct_form) {
        auto [matam, data, _] = GetParam();

        std::stringstream out;
        std::stringstream expectedOut;

        out << matam;

        expectedOut << string("Movie Name: ") + "authName" << std::endl;
        expectedOut << string("Author: ") + "creator" << std::endl;

        for (size_t r = 0; r < data.size(); r++) {
            expectedOut << "Frame " + std::to_string(r) + ":" << std::endl;
            expectedOut << matam[(int)r] << std::endl;
        }
        expectedOut << "-----End of Movie-----" << std::endl;

        EXPECT_EQ(expectedOut.str(), out.str());
    }

    INSTANTIATE_TEST_SUITE_P(Operators,
                             MataMvidiaOperatorsFixture,
                             testing::ValuesIn(
                                     MataMvidiaOperatorsFixture::testValues()
                             )
    );
}
