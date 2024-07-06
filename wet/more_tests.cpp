#include <iostream>
#include <string>
#include <cassert>
#include <sstream>

#include "Matrix.h"
#include "MataMvidia.h"

using namespace std;

// Assert macro with better error reporting
#define ASSERT_TEST(expr) do { \
    if (!(expr)) { \
        cout << "Assertion failed at " << __FILE__ << ":" << __LINE__ << ": " << #expr << endl; \
        exit(1); \
    } \
} while (0)

// Test functions declarations
bool testMatrixInitializationAndOperations();
bool testMataMvidiaOperations();
bool testMatrixTransformations();
bool testNonSquareMatrixTransformations();
void runAllTests();

int main() {
    runAllTests();
    cout << "All tests passed successfully!" << endl;
    return 0;
}

// Test matrix initialization and basic operations
bool testMatrixInitializationAndOperations() {
    Matrix m1(2, 2), m2(2, 2), m3;
    m1(0,0) = 1; m1(0,1) = 2; m1(1,0) = 3; m1(1,1) = 4;
    m2(0,0) = 5; m2(0,1) = 6; m2(1,0) = 7; m2(1,1) = 8;

    // Test addition
    m3 = m1 + m2;
    ASSERT_TEST(m3(0,0) == 6 && m3(0,1) == 8 && m3(1,0) == 10 && m3(1,1) == 12);

    // Test multiplication by scalar
    m3 = m1 * 3;
    ASSERT_TEST(m3(0,0) == 3 && m3(0,1) == 6 && m3(1,0) == 9 && m3(1,1) == 12);

    // Test transpose
    m3 = m1.transpose();
    ASSERT_TEST(m3(0,0) == 1 && m3(0,1) == 3 && m3(1,0) == 2 && m3(1,1) == 4);

    // Test rotation
    m3 = m1.rotateClockwise();
    ASSERT_TEST(m3(0,0) == 3 && m3(0,1) == 1 && m3(1,0) == 4 && m3(1,1) == 2);

    return true;
}

// Test MataMvidia movie operations
bool testMataMvidiaOperations() {
    Matrix frame1(2,2), frame2(2,2);
    frame1(0,0) = 1; frame1(0,1) = 2; frame1(1,0) = 3; frame1(1,1) = 4;
    frame2(0,0) = 5; frame2(0,1) = 6; frame2(1,0) = 7; frame2(1,1) = 8;

    Matrix frames[] = {frame1, frame2};
    MataMvidia movie("Test Movie", "Author", frames, 2);

    // Test movie indexing
    ASSERT_TEST(movie[0] == frame1 && movie[1] == frame2);

    // Test addition of frame
    movie += frame1;
    ASSERT_TEST(movie[2] == frame1);

    return true;
}

bool testMatrixTransformations() {
    // Create matrices of various sizes
    Matrix m1(3, 3), m2(1, 4), m3(4, 1);
    // Initialize m1 as a 3x3 matrix
    m1(0,0) = 1; m1(0,1) = 2; m1(0,2) = 3;
    m1(1,0) = 4; m1(1,1) = 5; m1(1,2) = 6;
    m1(2,0) = 7; m1(2,1) = 8; m1(2,2) = 9;
    // Initialize m2 as a 1x4 matrix
    m2(0,0) = 1; m2(0,1) = 2; m2(0,2) = 3; m2(0,3) = 4;
    // Initialize m3 as a 4x1 matrix
    m3(0,0) = 1; m3(1,0) = 2; m3(2,0) = 3; m3(3,0) = 4;

    // Test transpose functionality
    Matrix mt1 = m1.transpose();
    ASSERT_TEST(mt1(0,0) == 1 && mt1(1,0) == 2 && mt1(2,0) == 3);
    ASSERT_TEST(mt1(0,1) == 4 && mt1(1,1) == 5 && mt1(2,1) == 6);
    ASSERT_TEST(mt1(0,2) == 7 && mt1(1,2) == 8 && mt1(2,2) == 9);

    Matrix mt2 = m2.transpose();
    ASSERT_TEST(mt2(0,0) == 1 && mt2(1,0) == 2 && mt2(2,0) == 3 && mt2(3,0) == 4);

    Matrix mt3 = m3.transpose();
    ASSERT_TEST(mt3(0,0) == 1 && mt3(0,1) == 2 && mt3(0,2) == 3 && mt3(0,3) == 4);

    // Test rotation clockwise
    Matrix mcw1 = m1.rotateClockwise();
    ASSERT_TEST(mcw1(0,0) == 7 && mcw1(0,1) == 4 && mcw1(0,2) == 1);
    ASSERT_TEST(mcw1(1,0) == 8 && mcw1(1,1) == 5 && mcw1(1,2) == 2);
    ASSERT_TEST(mcw1(2,0) == 9 && mcw1(2,1) == 6 && mcw1(2,2) == 3);

    // Test rotation counterclockwise
    Matrix mccw1 = m1.rotateCounterClockwise();
    ASSERT_TEST(mccw1(0,0) == 3 && mccw1(0,1) == 6 && mccw1(0,2) == 9);
    ASSERT_TEST(mccw1(1,0) == 2 && mccw1(1,1) == 5 && mccw1(1,2) == 8);
    ASSERT_TEST(mccw1(2,0) == 1 && mccw1(2,1) == 4 && mccw1(2,2) == 7);

    // Test identity rotations
    Matrix mid = m1.rotateClockwise().rotateCounterClockwise();
    ASSERT_TEST(mid == m1);

    Matrix mid2 = m1.rotateCounterClockwise().rotateClockwise();
    ASSERT_TEST(mid2 == m1);

    // Test consecutive rotations
    Matrix m4x4(4, 4); // Create a 4x4 matrix for testing multiple rotations
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            m4x4(i, j) = i * 4 + j + 1;
        }
    }
    Matrix r90 = m4x4.rotateClockwise();
    Matrix r180 = r90.rotateClockwise();
    Matrix r270 = r180.rotateClockwise();
    Matrix r360 = r270.rotateClockwise();
    ASSERT_TEST(r360 == m4x4);

    // Ensure transpose of transpose is original
    ASSERT_TEST(m4x4.transpose().transpose() == m4x4);

    return true;
}

bool testNonSquareMatrixTransformations() {
    // Create non-square matrices
    Matrix m1(2, 3), m2(3, 2);

    // Initialize m1 as a 2x3 matrix
    m1(0,0) = 1; m1(0,1) = 2; m1(0,2) = 3;
    m1(1,0) = 4; m1(1,1) = 5; m1(1,2) = 6;

    // Initialize m2 as a 3x2 matrix
    m2(0,0) = 1; m2(0,1) = 2;
    m2(1,0) = 3; m2(1,1) = 4;
    m2(2,0) = 5; m2(2,1) = 6;

    // Test transpose functionality
    Matrix mt1 = m1.transpose();
    ASSERT_TEST(mt1(0,0) == 1 && mt1(1,0) == 2 && mt1(2,0) == 3);
    ASSERT_TEST(mt1(0,1) == 4 && mt1(1,1) == 5 && mt1(2,1) == 6);

    Matrix mt2 = m2.transpose();
    ASSERT_TEST(mt2(0,0) == 1 && mt2(0,1) == 3 && mt2(0,2) == 5);
    ASSERT_TEST(mt2(1,0) == 2 && mt2(1,1) == 4 && mt2(1,2) == 6);

    // Test scalar multiplication
    Matrix ms1 = m1 * 2;
    ASSERT_TEST(ms1(0,0) == 2 && ms1(0,1) == 4 && ms1(0,2) == 6);
    ASSERT_TEST(ms1(1,0) == 8 && ms1(1,1) == 10 && ms1(1,2) == 12);

    Matrix ms2 = m2 * 3;
    ASSERT_TEST(ms2(0,0) == 3 && ms2(0,1) == 6);
    ASSERT_TEST(ms2(1,0) == 9 && ms2(1,1) == 12);
    ASSERT_TEST(ms2(2,0) == 15 && ms2(2,1) == 18);

    // Test the transpose of the transpose returns the original matrix
    ASSERT_TEST(m1.transpose().transpose() == m1);
    ASSERT_TEST(m2.transpose().transpose() == m2);

    // Ensure transposing multiple times toggles between the two configurations
    ASSERT_TEST(m1.transpose().transpose().transpose() == m1.transpose());
    ASSERT_TEST(m2.transpose().transpose().transpose() == m2.transpose());

    return true;
}

bool testConstructorDeepCopy() {
    // Testing for Matrix class
    Matrix m1(2, 2);
    m1(0,0) = 1; m1(0,1) = 2;
    m1(1,0) = 3; m1(1,1) = 4;

    // Use copy constructor
    Matrix m2(m1);
    // Change original matrix
    m1(0,0) = 5;

    // m2 should remain unchanged if a deep copy was made
    ASSERT_TEST(m2(0,0) == 1);
    ASSERT_TEST(m2(0,1) == 2);
    ASSERT_TEST(m2(1,0) == 3);
    ASSERT_TEST(m2(1,1) == 4);

    // Testing for MataMvidia class
    Matrix frames[] = {Matrix(1,1), Matrix(1,1)};
    frames[0](0,0) = 10;
    frames[1](0,0) = 20;

    MataMvidia movie1("Original", "Author", frames, 2);

    // Use copy constructor
    MataMvidia movie2(movie1);
    // Change original movie frames
    movie1[0](0,0) = 30;

    // movie2 should remain unchanged if a deep copy was made
    ASSERT_TEST(movie2[0](0,0) == 10);
    ASSERT_TEST(movie2[1](0,0) == 20);

    return true;
}

bool testMataMvidiaOperatorLogic() {
    // Create initial Matrix frames
    Matrix frame1(2,2), frame2(2,2);
    frame1(0,0) = 1; frame1(0,1) = 2; frame1(1,0) = 3; frame1(1,1) = 4;
    frame2(0,0) = 5; frame2(0,1) = 6; frame2(1,0) = 7; frame2(1,1) = 8;

    // Create initial MataMvidia objects
    Matrix frames[] = {frame1, frame2};
    MataMvidia movie1("First Movie", "Author A", frames, 2);

    // Test indexing operator
    ASSERT_TEST(movie1[0] == frame1);
    ASSERT_TEST(movie1[1] == frame2);

    // Test addition of a single frame
    movie1 += frame1;
    ASSERT_TEST(movie1[2] == frame1);  // Implicitly tests that length increased

    // Test addition of another MataMvidia object
    MataMvidia movie2("Second Movie", "Author B", frames, 2);
    MataMvidia combinedMovie = movie1 + movie2;
    ASSERT_TEST(combinedMovie[4] == frame2);  // Checks last frame to infer total length

    // Additional tests for logical operations using indexing and result checking
    for (int i = 0; i < 10; ++i) {
        movie1 += frame2;  // Adding frames and checking the last added
        ASSERT_TEST(movie1[i + 3] == frame2);  // i+3 to account for initial frames and first addition
    }

    return true;
}


bool testMataMvidiaCopyAndAssignment() {
    // Create Matrix frames
    Matrix frame1(2,2), frame2(2,2);
    frame1(0,0) = 1; frame1(0,1) = 2; frame1(1,0) = 3; frame1(1,1) = 4;
    frame2(0,0) = 5; frame2(0,1) = 6; frame2(1,0) = 7; frame2(1,1) = 8;

    // Initial MataMvidia object
    Matrix frames[] = {frame1, frame2};
    MataMvidia original("Original", "Author", frames, 2);

    // Copy constructor test
    MataMvidia copyConstructed(original);
    ASSERT_TEST(copyConstructed[0] == original[0]);
    ASSERT_TEST(copyConstructed[1] == original[1]);

    // Assignment operator test
    MataMvidia assigned;
    assigned = original;
    ASSERT_TEST(assigned[0] == original[0]);
    ASSERT_TEST(assigned[1] == original[1]);

    // Modify original and ensure copies are unaffected
    original[0](0,0) = 10;
    ASSERT_TEST(copyConstructed[0](0,0) == 1);
    ASSERT_TEST(assigned[0](0,0) == 1);

//    // Test self-assignment
//    original = original;
//    ASSERT_TEST(original[0](0,0) == 10);

    // Additional deep copy tests
    for (int i = 0; i < 10; ++i) {
        MataMvidia newCopy = original;
        original[i % 2](0,0) += 5;
        ASSERT_TEST(newCopy[i % 2](0,0) != original[i % 2](0,0));
    }

    return true;
}


bool testMatrixPrintOperator() {
    std::stringstream ss;

    // Test 1: Empty Matrix
    Matrix m1;
    ss << m1;
    ASSERT_TEST(ss.str() == "");  // Assuming empty matrix prints nothing or some specific format
    ss.str("");  // Clear stringstream after each test

    // Test 2-5: Different Sizes and Contents
    Matrix m2(1, 1);
    m2(0, 0) = 1;
    ss << m2;
    ASSERT_TEST(ss.str() == "|1|\n");
    ss.str("");

    Matrix m3(2, 2);
    m3(0, 0) = 1; m3(0, 1) = 2;
    m3(1, 0) = 3; m3(1, 1) = 4;
    ss << m3;
    ASSERT_TEST(ss.str() == "|1|2|\n|3|4|\n");
    ss.str("");

    Matrix m4(2, 3);
    m4(0, 0) = -1; m4(0, 1) = -2; m4(0, 2) = -3;
    m4(1, 0) = 4;  m4(1, 1) = 5;  m4(1, 2) = 6;
    ss << m4;
    ASSERT_TEST(ss.str() == "|-1|-2|-3|\n|4|5|6|\n");
    ss.str("");

    Matrix m5(3, 1);
    m5(0, 0) = 7;
    m5(1, 0) = 8;
    m5(2, 0) = 9;
    ss << m5;
    ASSERT_TEST(ss.str() == "|7|\n|8|\n|9|\n");
    ss.str("");

    // Additional 15 tests for MataMvidia with various frame configurations
    Matrix frame1(1, 1);
    frame1(0, 0) = 1;
    Matrix frame2(1, 2);
    frame2(0, 0) = 2; frame2(0, 1) = 3;
    Matrix frame3(2, 1);
    frame3(0, 0) = 4; frame3(1, 0) = 5;
    Matrix frames[] = {frame1, frame2, frame3};

    MataMvidia movie1("Matrix Chronicles", "Neo", frames, 3);
    ss << movie1;
    std::string expectedMovieOutput = "Movie Name: Matrix Chronicles\nAuthor: Neo\n\n"
                                      "Frame 0:\n|1|\n\nFrame 1:\n|2|3|\n\nFrame 2:\n|4|\n|5|\n\n"
                                      "-----End of Movie-----";

    ASSERT_TEST(ss.str() == expectedMovieOutput);
    ss.str("");

    // Generate more MataMvidia tests with varying contents and lengths up to 20 total tests

    return true;
}

void runAllTests() {
    ASSERT_TEST(testMatrixInitializationAndOperations());
    ASSERT_TEST(testMataMvidiaOperations());
    ASSERT_TEST(testMatrixTransformations());
    ASSERT_TEST(testNonSquareMatrixTransformations());
    ASSERT_TEST(testConstructorDeepCopy());
    ASSERT_TEST(testMataMvidiaOperatorLogic());
    ASSERT_TEST(testMataMvidiaCopyAndAssignment());
    ASSERT_TEST(testMatrixPrintOperator());
}
