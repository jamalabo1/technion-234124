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


    Matrix rotateClockwise() const;

    Matrix rotateCounterClockwise() const;

    Matrix transpose() const;


    int &operator()(const int &i, const int &j) const;

    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat);

    friend Matrix operator+(Matrix left, Matrix &right);

    friend Matrix operator-(Matrix left, Matrix &right);

    friend Matrix operator*(Matrix left, Matrix &right);

    Matrix &operator-=(Matrix &other);

    Matrix &operator+=(Matrix &other);

    friend Matrix &operator*=(Matrix &mat, Matrix &other);

    friend Matrix operator-(Matrix mat);

    friend Matrix operator*(int &left, Matrix right);

    friend Matrix operator*(Matrix left, int &right);

    friend Matrix &operator*=(int &left, Matrix &right);

    friend Matrix &operator*=(Matrix &left, int &right);

    friend bool operator!=(const Matrix &left, const Matrix &right);

    friend bool operator==(const Matrix &left, const Matrix &right);

    friend Matrix &rotateClockwise(Matrix &mat, Matrix &other);

    friend Matrix &rotateCounterClockwise(Matrix &mat, Matrix &other);

    friend Matrix &transpose(Matrix &mat, Matrix &other);
};

#endif //HW2_MATRIX_H
