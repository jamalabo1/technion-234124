//
// Created by Farah Qub on 06/07/2024.
//
#include "Matrix.h"

using std::endl;

Matrix::Matrix(int row, int col) : rows(row), cols(col) {
    data = new int[row * col]{0};
}

Matrix::Matrix() : Matrix(0, 0) {
}

Matrix::~Matrix() {
    delete[] data;
}

int &Matrix::operator()(const int &i, const int &j) const {
    return data[i * rows + j];
}

std::ostream &operator<<(std::ostream &os, const Matrix &mat) {
    for (int r = 0; r < mat.rows; r++) {
        for (int c = 0; c < mat.cols; c++) {
            os << mat(r, c);
            if (c != mat.cols) {
                os << "|";
            }
        }
        os << endl;
    }
    return os;
}

///the sumpion of two matrixes
Matrix operator+(Matrix left, Matrix &right) {
    if(left.rows != right.rows || left.cols != right.cols){
        return 0;
    }
    for (int r = 0; r < left.rows; r++) {
        for (int c = 0; c < left.cols; c++) {
            left(r, c) += right(r, c);
        }
    }
    return left;
}

//subtraction for two matrixesS
Matrix operator-(Matrix left, Matrix &right) {
    if(left.rows != right.rows || left.cols != right.cols){
        return 0;
    }
    for (int r = 0; r < left.rows; r++) {
        for (int c = 0; c < left.cols; c++) {
            left(r, c) -= right(r, c);
        }
    }
    return left;
}

///multiplation for two matrixes
Matrix operator*(Matrix left, Matrix &right) {
    if(left.rows != right.rows || left.cols != right.cols){
        return 0;
    }
    for (int r = 0; r < left.rows; r++) {
        for (int c = 0; c < left.cols; c++) {
            left(r, c) -= right(r, c);
        }
    }
    return left;
}


Matrix& Matrix::operator-=( Matrix &other){
    Matrix inv = -other;
    (*this) += inv;
    return *this;
}

Matrix&  Matrix::operator+=( Matrix &other){
    for (int r = 0; r < this->rows; r++) {
        for (int c = 0; c < this->cols; c++) {
            other(r, c) += this->operator()(r, c);
        }
    }
    return other;
}

Matrix& operator*=(Matrix &mat, Matrix &other){
    for (int r = 0; r < mat.rows; r++) {
        for (int c = 0; c < mat.cols; c++) {
            other(r, c) *= mat(r, c);
        }
    }
    return other;
}

Matrix operator-(Matrix mat){
    for (int r = 0; r < mat.rows; r++) {
        for (int c = 0; c < mat.cols; c++) {
            mat(r, c) = -mat(r, c);
        }
    }
    return mat;
}

Matrix operator*(int &left, Matrix right) {
    for (int r = 0; r < right.rows; r++) {
        for (int c = 0; c < right.cols; c++) {
            right(r, c) *= left;
        }
    }
    return right;
}

Matrix operator*(Matrix left, int &right) {
    for (int r = 0; r < left.rows; r++) {
        for (int c = 0; c < left.cols; c++) {
            left(r, c) *= right;
        }
    }
    return left;
}

Matrix& operator*=(int &left, Matrix &right) {
    for (int r = 0; r < right.rows; r++) {
        for (int c = 0; c < right.cols; c++) {
            right(r, c) *= left;
        }
    }
    return right;
}

Matrix& operator*=(Matrix &left, int &right) {
    for (int r = 0; r < left.rows; r++) {
        for (int c = 0; c < left.cols; c++) {
            left(r, c) *= right;
        }
    }
    return left;
}

bool operator==(const Matrix &left, const Matrix &right){
    if(left.rows != right.rows || left.cols != right.cols){
        return 0;
    }
    for (int r = 0; r < left.rows; r++) {
        for (int c = 0; c < left.cols; c++) {
            if(right(r, c) != left(r, c)){
                return false;
            }
        }
     }
     return true;
}

bool operator!=(const Matrix &left, const Matrix &right){
    if(left.rows != right.rows || left.cols != right.cols){
        return 0;
    }
    for (int r = 0; r < left.rows; r++) {
        for (int c = 0; c < left.cols; c++) {
            if(right(r, c) == left(r, c)){
                return false;
            }
        }
     }
     return true;
}


Matrix& rotateClockwise(Matrix &mat, Matrix &other){
    other.rows = mat.cols;
    other.cols = mat.rows;
    for (int r = 0; r < mat.rows; r++) {
        for (int c = 0; c < mat.cols; c++) {
            other(c, mat.rows - 1 - r) = mat(r, c);
        }
    }
    return other;
}

Matrix& rotateCounterClockwise(Matrix &mat, Matrix &other){
    other.rows = mat.cols;
    other.cols = mat.rows;
    for (int r = 0; r < mat.rows; r++) {
        for (int c = 0; c < mat.cols; c++) {
            other(mat.cols - 1 -c, r) = mat(r, c);
        }
    }
    return other;
}

Matrix& transpose(Matrix &mat, Matrix &other){
    other.rows = mat.cols;
    other.cols = mat.rows;
    for (int r = 0; r < mat.rows; r++) {
        for (int c = 0; c < mat.cols; c++) {
            other(c, r) = mat(r, c);
        }
    }
    return other;
}
