//
// Created by Farah Qub on 06/07/2024.
//

#ifndef HW2_MATAMVIDIA_H
#define HW2_MATAMVIDIA_H


#include <string>
#include "Matrix.h"


class MataMvidia {
private:
    std::string name;
    std::string creator;
    Matrix *frames;
    int length;

    void appendToFrames(Matrix rightFrames[], int rightLength);

    friend Matrix *copyFrames(const MataMvidia &other);

public:

    MataMvidia(std::string name, std::string creator, Matrix *frames, int length);

    MataMvidia();

    MataMvidia(const MataMvidia &);

    MataMvidia &operator=(const MataMvidia &other);


    ~MataMvidia();

    Matrix &operator[](int index);

    const Matrix &operator[](int index) const;

    MataMvidia &operator+=(const MataMvidia &right);

    MataMvidia &operator+=(const Matrix &right);


    friend std::ostream &operator<<(std::ostream &os, const MataMvidia &movie);
};

MataMvidia operator+(const MataMvidia &left, const MataMvidia &right);

#endif //HW2_MATAMVIDIA_H
