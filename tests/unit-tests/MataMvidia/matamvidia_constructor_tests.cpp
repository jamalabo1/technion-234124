//
// Created by jamal on 14/07/2024.
//

#include <gtest/gtest.h>

#include <MataMvidia.h>
#include <tuple>
#include "utils.h"

namespace {

    using std::tuple;
    using std::vector;
    using std::string;

    class MataMvidiaFixture : public ::testing::TestWithParam<tuple<MataMvidia, vector<Matrix>>> {
    public:
        static vector<ParamType> testValues() {
            vector<ParamType> result;
            int len = testUtils::generateRandomNumber(1, 30);
            for (int i = 0; i < len; i++) {
                auto dims = testUtils::generateRandomDims(10);
                vector<Matrix> matPack;
                for (auto [rows, cols]: dims) {
                    auto [mat, _] = testUtils::generateMatrix(rows, cols);
                    matPack.emplace_back(
                            mat
                    );
                }
                MataMvidia mataMvidia("authName", "creator", matPack.data(), (int) matPack.size());
                result.emplace_back(mataMvidia, matPack);
            }
            return result;
        }
    };

    class MataMvidiaConstructorFixture : public testing::TestWithParam<tuple<string, string, vector<Matrix>, int>> {
    };

    class MataMvidiaCopyFixture : public MataMvidiaFixture {
    };

    TEST_P(MataMvidiaConstructorFixture, MataMvidiaConstuctor_initiates_sucessfully) {
        auto [author, creator, frames, len] = GetParam();
        EXPECT_NO_THROW({
                            MataMvidia MataMvidia(author, creator, frames.data(), len);
                        });
    }

    TEST_P(MataMvidiaCopyFixture, MataMvidiaConstuctor_copies_matamvidia) {
        auto [matam, _] = GetParam();

        MataMvidia copy(matam);

        EXPECT_NE(&copy, &matam);

        EXPECT_MATAM_EQ(copy, matam);
    }

    TEST_P(MataMvidiaCopyFixture, MataMvidiaConstuctor_copy_assignment) {
        auto [matam, _] = GetParam();

        MataMvidia copy = matam;

        EXPECT_NE(&copy, &matam);



        EXPECT_MATAM_EQ(copy, matam);
    }

    INSTANTIATE_TEST_SUITE_P(Constructor,
                             MataMvidiaConstructorFixture,
                             testing::Values(
                                     tuple("author", "creator", vector<Matrix>(), 0),
                                     tuple("author", "creator", vector<Matrix>{Matrix(0, 0), Matrix(1, 1)}, 2),
                                     tuple("", "creator", vector<Matrix>(), 0),
                                     tuple("author", "", vector<Matrix>(), 0)
                             )
    );

    INSTANTIATE_TEST_SUITE_P(Constructor,
                             MataMvidiaCopyFixture,
                             testing::ValuesIn(
                                     MataMvidiaCopyFixture::testValues()
                             )
    );
}
