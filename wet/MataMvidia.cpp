//
// Created by Farah Qub on 06/07/2024.
//
#include "MataMvidia.h"
#include <Utilities.h>

using std::endl;
using std::string;
using std::to_string;

Matrix *copyArray(Matrix *arr, int n) {
    Matrix *result = new Matrix[n];
    for (int i = 0; i < n; i++) {
        result[i] = arr[i];
    }
    return result;
}

MataMvidia::MataMvidia(string name, string creator, Matrix *frames, int length) :
        name(name), creator(creator), length(length) {

    this->frames = copyArray(frames, length);
}

MataMvidia::MataMvidia() {
    length = 0;
}


MataMvidia::~MataMvidia() {
    delete[] frames;
}

Matrix &MataMvidia::operator[](int index) {
    if (index < 0 || index >= length) {
        exitWithError(MatamErrorType::OutOfBounds);
    }

    return frames[index];
}

MataMvidia &MataMvidia::operator=(const MataMvidia &other) {
    if (this == &other) return *this;

    this->name = other.name;
    this->length = other.length;
    this->creator = other.creator;


    delete[] this->frames;

    this->frames = copyFrames(other);

    return *this;
}

MataMvidia::MataMvidia(const MataMvidia &other) : name(other.name), creator(other.creator), length(other.length) {
    this->frames = copyFrames(other);
}

Matrix *merge(Matrix a1[], int l1, Matrix a2[], int l2) {
    Matrix *mat = new Matrix[l1 + l2];
    for (int i = 0; i < l1; i++) {
        mat[i] = a1[i];
    }
    for (int i = 0; i < l2; i++) {
        mat[i + l1] = a2[i];
    }
    return mat;
}

void MataMvidia::appendToFrames(Matrix *rightFrames, int rightLength) {
    Matrix *temp = this->frames;
    this->frames = merge(temp, this->length, rightFrames, rightLength);
    this->length += rightLength;
    delete[] temp;
}

MataMvidia &MataMvidia::operator+=(const MataMvidia &right) {

    this->appendToFrames(right.frames, right.length);

    return *this;
}

MataMvidia &MataMvidia::operator+=(const Matrix &right) {

    Matrix *temp = new Matrix[1]{right};
    this->appendToFrames(temp, 1);
    delete[] temp;

    return *this;
}


MataMvidia operator+(MataMvidia left, const MataMvidia &right) {
    left += right;
    return left;
}


std::ostream &operator<<(std::ostream &os, const MataMvidia &movie) {
    os << "Movie Name: " + movie.name << endl;
    os << "Author: " + movie.creator << endl;

    for (int r = 0; r < movie.length; r++) {
        os << "Frame " + to_string(r) + ":" << endl;
        os << movie[r];
    }
    return os;
}

const Matrix &MataMvidia::operator[](int index) const {
    return frames[index];
}


Matrix *copyFrames(const MataMvidia &other) {
    Matrix *frames = new Matrix[other.length];
    for (int i = 0; i < other.length; i++) {
        frames[i] = other.frames[i];
    }
    return frames;
}

