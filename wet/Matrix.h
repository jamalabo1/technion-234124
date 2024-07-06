//
// Created by Farah Qub on 06/07/2024.
//

#ifndef HW2_MATRIX_H
#define HW2_MATRIX_H

#include <ostream>

class Matrix {
private:
    int *data;
    int rows;
    int cols;


public:
    Matrix(int row, int col);

    Matrix();

    ~Matrix();


    int &operator()(const int &i, const int &j) const;


    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat);

    friend Matrix operator+(Matrix left, Matrix &right);
    friend Matrix& operator+=(Matrix& mat, Matrix& other);

};

#endif //HW2_MATRIX_H
