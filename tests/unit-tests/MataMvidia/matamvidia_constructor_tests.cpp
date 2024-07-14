//
// Created by jamal on 14/07/2024.
//

#include <gtest/gtest.h>

#include <MataMvidia.h>

namespace {

    using std::tuple;

    class MataMvidiaTestFixture :
            public ::testing::TestWithParam<tuple<int, int>> {
    };

    class MataMvidiaTestInvalidDataFixture : public MataMvidiaTestFixture {
    };

    class MataMvidiaConstructorFixture : public MataMvidiaTestFixture {
    };

//    TEST_P(MataMvidiaTestConstructorFixture, MataMvidiaConstuctor_initiates_sucessfully
//    ) {
//        const auto [rows, cols] = GetParam();
//        EXPECT_NO_THROW({
//                            MataMvidia MataMvidia(rows, cols);
//                        });
//    }
//
//    TEST_P(MataMvidiaTestConstructorFixture, MataMvidiaConstuctor_defaults_data_at_zero
//    ) {
//        const auto [rows, cols] = GetParam();
//        MataMvidia MataMvidia(rows, cols);
//
//        for (
//                int i = 0;
//                i < rows;
//                i++) {
//            for (
//                    int j = 0;
//                    j < cols;
//                    j++) {
//                EXPECT_EQ(MataMvidia(i, j),
//                          0);
//            }
//        }
//    }
//
//    TEST_P(MataMvidiaTestConstructorFixture, MataMvidiaConstuctor_copies_MataMvidia
//    ) {
//        const auto [rows, cols] = GetParam();
//        MataMvidia MataMvidia(rows, cols);
//
//        MataMvidia copy(MataMvidia);
//
//        EXPECT_NE(&copy, &MataMvidia
//        );
//
//        EXPECT_EQ(MataMvidia, copy
//        );
//    }
//
//    TEST_P(MataMvidiaTestConstructorFixture, MataMvidiaConstuctor_copy_assignment
//    ) {
//        const auto [rows, cols] = GetParam();
//        MataMvidia MataMvidia(rows, cols);
//
//        MataMvidia copy = MataMvidia;
//
//        EXPECT_NE(&copy, &MataMvidia
//        );
//
//        EXPECT_EQ(MataMvidia, copy
//        );
//    }
//
//
//    TEST_P(MataMvidiaTestInvalidDataFixture, MataMvidiaConstuctor_throws_expection_on_invalid_d
//    ) {
//        const auto [rows, cols] = GetParam();
//
//        EXPECT_DEATH({
//                         MataMvidia MataMvidia(rows, cols);
//                     }, "Out of bounds");
//    }
//
//    INSTANTIATE_TEST_SUITE_P(Constructor,
//                             MataMvidiaTestInvalidDimsFixture,
//                             testing::Values(
//                                     tuple(-1, 0),
//                                     tuple(0, -1),
//                                     tuple(-1, -1),
//                                     tuple(1, -1),
//                                     tuple(-1, 1)
//                             )
//    );
//
//    INSTANTIATE_TEST_SUITE_P(Constructor,
//                             MataMvidiaTestConstructorFixture,
//                             testing::Values(
//                                     tuple(0, 0),
//                                     tuple(1, 1),
//                                     tuple(1, 10),
//                                     tuple(10, 1),
//                                     tuple(3, 3)
//                             )
//    );
}
