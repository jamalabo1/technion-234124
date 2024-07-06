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

Matrix Matrix::operator+(Matrix left, Matrix &right) {
    left += right;
    return left;
}

Matrix &operator+=(Matrix &mat, Matrix &other) {

}
