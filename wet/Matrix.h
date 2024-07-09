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

    int at(const int &i, const int &j) const;

    friend int *copyArray(const Matrix &A);

    void copyDataFrom(const Matrix &A);

public:
    Matrix(int row, int col);

    Matrix();

    Matrix(const Matrix &);

    Matrix &operator=(const Matrix &other);     // copy assignment operator

    ~Matrix();


//    Matrix rotateClockwise() const;
//
//    Matrix rotateCounterClockwise() const;
//
//    Matrix transpose() const;


    int &operator()(const int &i, const int &j);

    const int &operator()(const int &i, const int &j) const;


    Matrix &operator*=(const Matrix &other);

    Matrix &operator+=(const Matrix &other);

    Matrix &operator-=(const Matrix &other);

    Matrix &operator*=(int right);


    friend Matrix operator+(Matrix left, const Matrix &right);

    friend Matrix operator-(Matrix left, const Matrix &right);

    friend Matrix operator*(Matrix left, const Matrix &right);

    friend Matrix operator-(const Matrix &mat);


    friend Matrix operator*(int left, Matrix right);

    friend Matrix operator*(Matrix left, int right);

    friend Matrix &operator*=(int left, Matrix &right);


    friend bool operator==(const Matrix &left, const Matrix &right);

    friend bool operator!=(const Matrix &left, const Matrix &right);

    Matrix rotateClockwise();

    Matrix rotateCounterClockwise();

    Matrix transpose();

    friend std::ostream &operator<<(std::ostream &os, const Matrix &mat);
};

#endif //HW2_MATRIX_H
