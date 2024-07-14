//
// Created by jamal on 12/07/2024.
#include <gtest/gtest.h>

#include <Matrix.h>
#include "MatrixTestBase.h"

namespace {

    using std::tuple;
    using std::vector;
    using testUtils::generateRandomNumber;
    using testUtils::generateRandomDims;
    using testUtils::Dim;

    class MatrixTestOperatorsBase : public MatrixTestBase {
    };

    class MatrixTestMethodsFixture :
            public MatrixTestOperatorsBase,
            public ::testing::TestWithParam<tuple<Matrix, int, int>> {
    public:
        using eqTestType = MatrixTestMethodsFixture::ParamType;

        static vector<eqTestType> testValues() {
            vector<eqTestType> data;
            auto dims = generateRandomDims(10);
            data.reserve(dims.size());
            for (const auto &[rows, cols]: dims) {
                auto [mat, matData] = generateMatrix(rows, cols);
                data.emplace_back(
                        mat, rows, cols

                );
            }
            return data;
        }
    };

    TEST_P(MatrixTestMethodsFixture, MatrixTranspose_flips_data) {
        const auto [mat, rows, cols] = GetParam();

        Matrix result = mat.transpose();

        for (int i = 0; i < cols; i++) {
            for (int j = 0; j < rows; j++) {
                EXPECT_EQ(result(i, j), mat(j, i));
            }
        }
    }

    TEST_P(MatrixTestMethodsFixture, MatrixRotateClockwise_flips_data) {
        const auto [mat, rows, cols] = GetParam();

        Matrix result = mat.rotateClockwise();

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                EXPECT_EQ(result(j, rows - 1 - i), mat(i, j));
            }
        }
    }

    TEST_P(MatrixTestMethodsFixture, MatrixCounterRotateClockwise_flips_data) {
        const auto [mat, rows, cols] = GetParam();

        Matrix result = mat.rotateCounterClockwise();

        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                EXPECT_EQ(result(cols - 1 - j, i), mat(i, j));
            }
        }
    }

    INSTANTIATE_TEST_SUITE_P(MatrixTestMethods,
                             MatrixTestMethodsFixture,
                             testing::ValuesIn(
                                     MatrixTestMethodsFixture::testValues()
                             ));
}
