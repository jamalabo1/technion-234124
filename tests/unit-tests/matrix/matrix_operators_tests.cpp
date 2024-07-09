//
// Created by jamal on 09/07/2024.
//
#include <gtest/gtest.h>

#include <Matrix.h>
#include "utils.h"
#include "MatrixTestBase.h"

namespace {

    using std::tuple;
    using std::vector;
    using testUtils::generateRandomNumber;
    using testUtils::generateRandomDims;
    using testUtils::Dim;

    struct TestInfo {
        int rows, cols;
        int i, j;
        int val;
    };

    class MatrixTestOperatorsBase : public MatrixTestBase {
    };

    class MatrixTestOperatorFixture : public MatrixTestOperatorsBase,
                                      public ::testing::TestWithParam<tuple<Matrix, vector<vector<int>>, Dim>> {
    public:
        using eqTestType = MatrixTestOperatorFixture::ParamType;

        static vector<eqTestType> testValues() {
            vector<eqTestType> data;
            auto dims = generateRandomDims(10);
            data.reserve(dims.size());
            for (const auto &[rows, cols]: dims) {
                auto [mat, matData] = generateMatrix(rows, cols);
                data.push_back(
                        {
                                mat, matData, {rows, cols}
                        }
                );
            }
            return data;
        }

    public:
        static tuple<Matrix, int, int> GetFParams() {
            auto [mat, _, dim] = GetParam();
            const auto [rows, cols] = dim;

            return {mat, rows, cols};
        }
    };

    class MatrixTestScalarMultiplyOperatorFixture
            : MatrixTestOperatorsBase,
              public ::testing::TestWithParam<tuple<Matrix, int, int, int>> {
    public:
        using eqTestType = MatrixTestScalarMultiplyOperatorFixture::ParamType;

        static vector<eqTestType> testValues() {
            vector<eqTestType> data;
            auto dims = generateRandomDims(10);
            data.reserve(dims.size());
            for (int i = 0; i < dims.size(); i++) {
                const auto [rows, cols] = dims[i];
                auto [mat, _] = generateMatrix(rows, cols);
                data.emplace_back(
                        mat, rows, cols, i

                );
            }
            return data;
        }
    };

    TEST_P(MatrixTestOperatorFixture, MatrixIndexAssignment_assigns_data) {
        auto [mat, rows, cols] = GetFParams();

        Matrix matrix(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                matrix(i, j) = mat(i, j);
                EXPECT_EQ(matrix(i, j), mat(i, j));
            }
        }
    }

    TEST_P(MatrixTestOperatorFixture, MatrixEqOperator_evaluates_truth_on_eq) {
        const auto [mat, rows, cols] = GetFParams();

        Matrix mat2(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                mat2(i, j) = mat(i, j);
                ASSERT_EQ(mat2(i, j), mat(i, j));
            }
        }

        EXPECT_EQ(mat, mat2);
    }

    TEST_P(MatrixTestOperatorFixture, MatrixPlusOperator_adds_matricies) {
        const auto [mat, rows, cols] = GetFParams();
        const auto mat2 = generateHelperMatrix(rows, cols);

        Matrix result = mat + mat2;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                EXPECT_EQ(result(i, j), mat(i, j) + mat2(i, j));
            }
        }
    }

    TEST_P(MatrixTestOperatorFixture, MatrixPlusEqOperator_adds_to_matrix) {
        auto [mat, rows, cols] = GetFParams();
        const auto mat2 = generateHelperMatrix(rows, cols);

        Matrix matCopy(mat);
        mat += mat2;

        EXPECT_EQ(mat, matCopy + mat2);
    }


    TEST_P(MatrixTestOperatorFixture, MatrixMultiplyOperator_multiplies_matricies) {
        auto [mat, rows, cols] = GetFParams();
        const auto mat2 = generateHelperMatrix(cols, rows);

        Matrix expectedResult(rows, rows);

        vector<vector<long>> results;
        for (int i = 0; i < rows; i++) {
            vector<long> row;
            for (int j = 0; j < rows; j++) {
                int sum = 0;
                for (int k = 0; k < cols; k++) {
                    sum += mat(i, k) * mat2(k, j);
                }
                row.emplace_back(sum);
            }
            results.emplace_back(row);
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < rows; j++) {
                expectedResult(i, j) = results[i][j];
            }
        }
        Matrix result = mat * mat2;

        EXPECT_EQ(result, expectedResult);
    }

    TEST_P(MatrixTestOperatorFixture, MatrixEqMultiplyOperator_multiplies_matrix) {
        auto [mat, rows, cols] = GetFParams();
        const auto mat2 = generateHelperMatrix(cols, cols);

        Matrix matCopy(mat);
        mat *= mat2;


        EXPECT_EQ(mat, matCopy * mat2);
    }


    TEST_P(MatrixTestOperatorFixture, MatrixAdditiveInverseOperator_returns_the_additive_inverse_in_field) {
        const auto [mat, rows, cols] = GetFParams();

        Matrix result = -mat;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                EXPECT_EQ(result(i, j), -mat(i, j));
            }
        }
    }

    TEST_P(MatrixTestOperatorFixture, MatrixMinusOperator_subtracts_matricies) {
        const auto [mat, rows, cols] = GetFParams();
        const auto mat2 = generateHelperMatrix(rows, cols);

        Matrix result = mat - mat2;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                EXPECT_EQ(result(i, j), mat(i, j) - mat2(i, j));
            }
        }
    }


    TEST_P(MatrixTestOperatorFixture, MatrixMinusEqOperator_subtracts_from_matrix) {
        auto [mat, rows, cols] = GetFParams();
        const auto mat2 = generateHelperMatrix(rows, cols);

        Matrix matCopy(mat);
        mat -= mat2;

        EXPECT_EQ(mat, matCopy - mat2);
    }


    TEST_P(MatrixTestScalarMultiplyOperatorFixture, MatrixMultiplyScalarOperator_multiplies_matrix_entiries) {
        auto [mat, rows, cols, scalar] = GetParam();

        Matrix result = mat * scalar;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                EXPECT_EQ(result(i, j), mat(i, j) * scalar);
            }
        }
    }

    TEST_P(MatrixTestScalarMultiplyOperatorFixture, MatrixMultiplyEqScalarOperator_multiplies_matrix) {
        auto [mat, _1, _2, scalar] = GetParam();

        Matrix matCopy(mat);
        mat *= scalar;

        EXPECT_EQ(mat, matCopy * scalar);
    }

    INSTANTIATE_TEST_SUITE_P(Operators,
                             MatrixTestOperatorFixture,
                             testing::ValuesIn(
                                     MatrixTestOperatorFixture::testValues()
                             )
    );

    INSTANTIATE_TEST_SUITE_P(Operators,
                             MatrixTestScalarMultiplyOperatorFixture,
                             testing::ValuesIn(
                                     MatrixTestScalarMultiplyOperatorFixture::testValues()
                             )
    );
}
