//
// Created by jamal on 09/07/2024.
//
#include <gtest/gtest.h>

#include <Matrix.h>

namespace {

    using std::tuple;

    struct TestInfo {
        int rows, cols;
        int i, j;
        int val;
    };

    class MatrixTestIndicesFixture :
            public ::testing::TestWithParam<TestInfo> {
    };

    TEST_P(MatrixTestIndicesFixture, MatrixAssignment_assigns_data) {
        const auto info = GetParam();
        Matrix matrix(info.rows, info.cols);

        ASSERT_EQ(matrix(info.i, info.j), 0);

        matrix(info.i, info.j) = info.val;

        EXPECT_EQ(matrix(info.i, info.j), info.val);
    }

    TEST_P(MatrixTestIndicesFixture, MatrixAssignment_can_access_all_indicies) {
        const auto info = GetParam();
        Matrix matrix(info.rows, info.cols);

        EXPECT_NO_THROW({
                            for (int i = 0; i < info.rows; i++) {
                                for (int j = 0; j < info.cols; j++) {
                                    matrix(i, j);
                                }
                            }
                        });
    }


    TEST_P(MatrixTestIndicesFixture, MatrixAssignment_throws_error_on_outofbound) {
        const auto info = GetParam();
        Matrix matrix(info.rows, info.cols);

        EXPECT_DEATH({ matrix(-1, 0); }, "Out of bounds");
        EXPECT_DEATH({ matrix(info.rows + 1, info.cols + 1); }, "Out of bounds");
        EXPECT_DEATH({ matrix(info.rows + 1, info.cols + 1) = 1; }, "Out of bounds");
    }


    INSTANTIATE_TEST_SUITE_P(Indices,
                             MatrixTestIndicesFixture,
                             testing::Values(
                                     TestInfo{1, 1, 0, 0, 0},
                                     TestInfo{1, 5, 0, 0, 0},
                                     TestInfo{1, 5, 0, 0, 1},
                                     TestInfo{5, 1, 0, 0, 1}
                             )
    );
}
