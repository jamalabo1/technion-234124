//
// Created by jamal on 09/07/2024.
//
#include <gtest/gtest.h>

#include <Matrix.h>

namespace {

    using std::tuple;

    class MatrixTestFixture :
            public ::testing::TestWithParam<tuple<int, int>> {
    };

    class MatrixTestInvalidDimsFixture : public MatrixTestFixture {
    };

    class MatrixTestConstructorFixture : public MatrixTestFixture {
    };

    TEST_P(MatrixTestConstructorFixture, MatrixConstuctor_initiates_sucessfully) {
        const auto [rows, cols] = GetParam();
        EXPECT_NO_THROW({ Matrix matrix(rows, cols); });
    }

    TEST_P(MatrixTestConstructorFixture, MatrixConstuctor_defaults_data_at_zero) {
        const auto [rows, cols] = GetParam();
        Matrix matrix(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                EXPECT_EQ(matrix(i, j), 0);
            }
        }
    }

    TEST_P(MatrixTestConstructorFixture, MatrixConstuctor_copies_matrix) {
        const auto [rows, cols] = GetParam();
        Matrix matrix(rows, cols);

        Matrix copy(matrix);

        EXPECT_NE(&copy, &matrix);

        EXPECT_EQ(matrix, copy);
    }

    TEST_P(MatrixTestConstructorFixture, MatrixConstuctor_copy_assignment) {
        const auto [rows, cols] = GetParam();
        Matrix matrix(rows, cols);

        Matrix copy = matrix;

        EXPECT_NE(&copy, &matrix);

        EXPECT_EQ(matrix, copy);
    }


    TEST_P(MatrixTestInvalidDimsFixture, MatrixConstuctor_throws_expection_on_invalid_dimensions) {
        const auto [rows, cols] = GetParam();

        EXPECT_DEATH({ Matrix matrix(rows, cols); }, "Out of bounds");
    }

    INSTANTIATE_TEST_SUITE_P(Constructor,
                             MatrixTestInvalidDimsFixture,
                             testing::Values(
                                     tuple(-1, 0),
                                     tuple(0, -1),
                                     tuple(-1, -1),
                                     tuple(1, -1),
                                     tuple(-1, 1)
                             )
    );

    INSTANTIATE_TEST_SUITE_P(Constructor,
                             MatrixTestConstructorFixture,
                             testing::Values(
                                     tuple(0, 0),
                                     tuple(1, 1),
                                     tuple(1, 10),
                                     tuple(10, 1),
                                     tuple(3, 3)
                             )
    );
}
