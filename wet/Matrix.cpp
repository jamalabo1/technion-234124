//
// Created by Farah Qub on 06/07/2024.
//
#include "Matrix.h"
#include "Utilities.h"

using std::endl;

Matrix::Matrix(int row, int col) : data(nullptr), rows(row), cols(col) {
    if (row < 0 || col < 0) {
        exitWithError(MatamErrorType::OutOfBounds);
        throw;
    }
    this->data = new int[row * col];
    for (int i = 0; i < row * col; i++) {
        data[i] = 0;
    }
}

Matrix::Matrix() : Matrix(0, 0) {
}

Matrix::~Matrix() {
    delete[] data;
}


void Matrix::copyDataFrom(const Matrix &other) {
//    delete[] this->data;
//    this->data = copyArray(A);
    if (other.data == nullptr) {
        this->data = nullptr;
        return;
    }

    delete[] data;
    data = new int[other.rows * other.cols];
    std::copy(other.data, other.data + (other.rows * other.cols), data);

    this->rows = other.rows;
    this->cols = other.cols;
}

// Copy Constructor
Matrix::Matrix(const Matrix &other) : data(nullptr), rows(other.rows), cols(other.cols) {
    this->copyDataFrom(other);
}


Matrix &Matrix::operator=(const Matrix &other) {
    if (this == &other) return *this;
    this->rows = other.rows;
    this->cols = other.cols;
    this->copyDataFrom(other);
    return *this;
}

void Matrix::validateIndices(const int &i, const int &j) const {
    if ((0 > i || i >= rows) || (0 > j || j >= cols)) {
        exitWithError(MatamErrorType::OutOfBounds);
    }
}

void Matrix::ensureMatchSize(const Matrix &other) const {
    if (other.rows != rows || other.cols != cols) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
}


int Matrix::at(const int &i, const int &j) const {
    this->validateIndices(i, j);
    return data[i * cols + j];
}


int &Matrix::operator()(const int &i, const int &j) {
    this->validateIndices(i, j);
    return data[i * cols + j];
}

const int &Matrix::operator()(const int &i, const int &j) const {
    this->validateIndices(i, j);
    return data[i * cols + j];
}


///multiplication for two matrices
Matrix &Matrix::operator*=(const Matrix &other) {
    if (this->cols != other.rows) {
        exitWithError(MatamErrorType::UnmatchedSizes);
    }
    Matrix result(this->rows, other.cols);

    for (int i = 0; i < result.rows; i++) {
        for (int j = 0; j < result.cols; j++) {
            int sum = 0;
            for (int k = 0; k < this->cols; k++) {
                sum += this->at(i, k) * other(k, j);
            }
            result(i, j) = sum;
        }
    }
    this->copyDataFrom(result);

    return (*this);
}

///multiplication for two matrices
Matrix operator*(const Matrix &left, const Matrix &right) {
    Matrix copy(left);
    copy *= right;
    return copy;
}


Matrix &Matrix::operator*=(int right) {
    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++) {
            (*this)(r, c) *= right;
        }
    }
    return *this;
}


Matrix &Matrix::operator+=(const Matrix &other) {
    ensureMatchSize(other);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            (*this)(r, c) += other(r, c);
        }
    }
    return *this;
}

///the summation of two matrices
Matrix operator+(const Matrix &left, const Matrix &right) {
    Matrix copy(left);

    copy += right;

    return copy;
}

//subtraction for two matrices
Matrix operator-(const Matrix &left, const Matrix &right) {
    Matrix copy(left);
    copy -= right;
    return copy;
}

Matrix operator*(int left, const Matrix &right) {
    Matrix copy(right);
    copy *= left;
    return copy;
}

Matrix operator*(const Matrix &left, int right) {
    return right * left;
}

Matrix operator-(const Matrix &mat) {
    return -1 * mat;
}

Matrix &Matrix::operator-=(const Matrix &other) {
    (*this) += -other;
    return *this;
}


bool operator==(const Matrix &left, const Matrix &right) {
    left.ensureMatchSize(right);

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
    return !(left == right);
}


Matrix Matrix::rotateClockwise() const {
    Matrix rotated(cols, rows);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            rotated(c, rows - 1 - r) = at(r, c);
        }
    }
    return rotated;
}

Matrix Matrix::rotateCounterClockwise() const {
    Matrix rotated(cols, rows);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            rotated(cols - 1 - c, r) = at(r, c);
        }
    }
    return rotated;
}


Matrix Matrix::transpose() const {
    Matrix transposed(cols, rows);

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            transposed(c, r) = at(r, c);
        }
    }
    return transposed;
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

//Matrix operator*(const Matrix &left, const Matrix &right) {
//    Matrix copy(left);
//
//    return copy * right;
//}
//
//Matrix operator+(const Matrix &left, const Matrix &right) {
//    Matrix copy(left);
//
//    return copy + right;
//}
//
//Matrix operator-(const Matrix &left, const Matrix &right) {
//    Matrix copy(left);
//
//    return copy - right;
//}
//
//Matrix operator*(int left, const Matrix &right) {
//    Matrix copy(left);
//    return left * copy;
//}
//
//Matrix operator*(const Matrix &left, int right) {
//    Matrix copy(left);
//
//    return copy * right;
//}