//
// Created by Farah Qub on 06/07/2024.
//
#include "Matrix.h"
#include "Utilities.h"


#define InsureSizeMatch(left, right) \
if(left.rows != right.rows || left.cols != right.cols){ \
exitWithError(MatamErrorType::UnmatchedSizes); \
}

using std::endl;

int *copy_array(const Matrix &A) {
    int *mdata = new int[A.rows * A.cols]{0};

    for (int i = 0; i < A.rows; i++) {
        for (int j = 0; j < A.cols; j++) {
            mdata[i * A.rows + j] = A(i, j);
        }
    }
    return mdata;
}

Matrix::Matrix(int row, int col) : rows(row), cols(col) {
    if (row == 0 || col == 0) {
        this->data = nullptr;
    } else {
        this->data = new int[row * col];
        for (int i = 0; i < row * col; i++) {
            data[i] = 0;
        }
    }
}

Matrix::Matrix() : Matrix(0, 0) {
}

Matrix::~Matrix() {
    delete[] data;
}

// Copy Constructor
Matrix::Matrix(const Matrix &A) : rows(A.rows), cols(A.cols) {
    this->data = copy_array(A);
}


Matrix &Matrix::operator=(const Matrix &other) {
    if (this == &other) return *this;
    delete[] this->data;
    this->rows = other.rows;
    this->cols = other.cols;
    this->data = copy_array(other);
    return *this;
}

//Matrix Matrix::operator=(Matrix other) {
//    this->rows = other.rows;
//    this->cols = other.cols;
//    this->data = copy_array(other);
//    return *this;
//}


int &Matrix::at(const int &i, const int &j) const {
    return data[i * rows + j];
}

int &Matrix::operator()(const int &i, const int &j) {
    return at(i, j);
}

const int &Matrix::operator()(const int &i, const int &j) const {
    return at(i, j);
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat) {
    for (int r = 0; r < mat.rows; r++) {
        for (int c = 0; c < mat.cols; c++) {
            os << mat(r, c);
            if (c + 1 != mat.cols) {
                os << "|";
            }
        }
        os << endl;
    }
    return os;
}

///the summation of two matrixes
Matrix operator+(Matrix left, const Matrix &right) {
    InsureSizeMatch(left, right);

    for (int r = 0; r < left.rows; r++) {
        for (int c = 0; c < left.cols; c++) {
            left(r, c) += right(r, c);
        }
    }
    return left;
}

//subtraction for two matrixesS
Matrix operator-(Matrix left, const Matrix &right) {
    InsureSizeMatch(left, right);

    for (int r = 0; r < left.rows; r++) {
        for (int c = 0; c < left.cols; c++) {
            left(r, c) -= right(r, c);
        }
    }
    return left;
}

///multiplation for two matrixes
Matrix operator*(Matrix left, const Matrix &right) {
    InsureSizeMatch(left, right);

    left *= right;
    return left;
}


Matrix &Matrix::operator-=(const Matrix &other) {
    Matrix inv = -other;
    (*this) += inv;
    return *this;
}

Matrix &Matrix::operator+=(const Matrix &other) {
    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++) {
            at(r, c) += other(r, c);
        }
    }
    return *this;
}

Matrix &Matrix::operator*=(const Matrix &other) {
    // TODO: insure multiply can be applied
    Matrix result(this->rows, other.cols);

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            int sum = 0;
            for (int k = 0; k < this->cols; k++) {
                sum += at(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    delete[] this->data;
    this->data = copy_array(result);
    return *this;
}

Matrix operator-(const Matrix &mat) {
    return -1 * mat;
}

Matrix operator*(int left, Matrix right) {
    for (int r = 0; r < right.rows; r++) {
        for (int c = 0; c < right.cols; c++) {
            right(r, c) *= left;
        }
    }
    return right;
}

Matrix operator*(Matrix left, int right) {
    for (int r = 0; r < left.rows; r++) {
        for (int c = 0; c < left.cols; c++) {
            left(r, c) *= right;
        }
    }
    return left;
}

Matrix &operator*=(int left, Matrix &right) {
    for (int r = 0; r < right.rows; r++) {
        for (int c = 0; c < right.cols; c++) {
            right(r, c) *= left;
        }
    }
    return right;
}

Matrix &operator*=(Matrix &left, int right) {
    for (int r = 0; r < left.rows; r++) {
        for (int c = 0; c < left.cols; c++) {
            left(r, c) *= right;
        }
    }
    return left;
}

bool operator==(const Matrix &left, const Matrix &right) {
    InsureSizeMatch(left, right);

    for (int r = 0; r < left.rows; r++) {
        for (int c = 0; c < left.cols; c++) {
            if (right(r, c) != left(r, c)) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const Matrix &left, const Matrix &right) {
    InsureSizeMatch(left, right);


    return !(left == right);
}


Matrix Matrix::rotateClockwise() {
    Matrix t(this->cols, this->rows);

    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++) {
            t(c, this->rows - 1 - r) = at(r, c);
        }
    }
    return t;
}

Matrix Matrix::rotateCounterClockwise() {
    Matrix t(this->cols, this->rows);

    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++) {
            t(t.cols - 1 - c, r) = at(r, c);
        }
    }
    return t;
}

Matrix Matrix::transpose() {
    Matrix t(this->cols, this->rows);

    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++) {
            t(c, r) = at(r, c);
        }
    }
    return t;
}


