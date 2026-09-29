#include "maths/matrix.h"


const float* Mat2::operator[](const int r) const { return &_arr[r * 2]; }

float* Mat2::operator[](const int r) { return &_arr[r * 2]; }

bool Mat2::operator==(const Mat2 operand) const { return (_arr == operand._arr); }; // FIXME: floating point percision

bool Mat2::operator!=(const Mat2 operand) const { return (_arr != operand._arr); }; // FIXME: floating point percision

Mat2 Mat2::operator*(const Mat2 operand) const {
    Mat2 v;

    for (int r=0; r < 2; r++) {
        for (int c=0; c < 2; c++) {
            v[r][c] = (
                _arr[r * 3] * operand[0][c] +
                _arr[r * 3 + 1] * operand[1][c]
            );
        }
    }

    return v;
}

Mat2& Mat2::operator*=(const Mat2 operand) {
    std::array<float, 4> v;

    for (int r=0; r < 2; r++) {
        for (int c=0; c < 2; c++) {
            v[r * 2 + c] = (
                _arr[r * 3] * operand[0][c] +
                _arr[r * 3 + 1] * operand[1][c]
            );
        }
    }

    _arr = v;

    return *this;
}

const float* Mat3::operator[](const int r) const { return &_arr[r * 3]; }

float* Mat3::operator[](const int r) { return &_arr[r * 3]; }

bool Mat3::operator==(const Mat3 operand) const { return (_arr == operand._arr); }; // FIXME: floating point percision

bool Mat3::operator!=(const Mat3 operand) const { return (_arr != operand._arr); }; // FIXME: floating point percision

Mat3 Mat3::operator*(const Mat3 operand) const {
    Mat3 v;

    for (int r=0; r < 3; r++) {
        for (int c=0; c < 3; c++) {
            v[r][c] = (
                _arr[r * 3] * operand[0][c] +
                _arr[r * 3 + 1] * operand[1][c] +
                _arr[r * 3 + 2] * operand[2][c]
            );
        }
    }

    return v;
}

Mat3& Mat3::operator*=(const Mat3 operand) {
    std::array<float, 9> v;

    for (int r=0; r < 3; r++) {
        for (int c=0; c < 3; c++) {
            v[r * 3 + c] = (
                _arr[r * 3] * operand[0][c] +
                _arr[r * 3 + 1] * operand[1][c] +
                _arr[r * 3 + 2] * operand[2][c]
            );
        }
    }

    _arr = v;

    return *this;
}

Tuple3 Mat3::operator*(const Tuple3 operand) const {
    Tuple3 v;

    v.x = (
        _arr[0] * operand.x +
        _arr[1] * operand.y +
        _arr[2] * operand.z
    );
    v.y = (
        _arr[4] * operand.x +
        _arr[5] * operand.y +
        _arr[6] * operand.z
    );
    v.z = (
        _arr[8] * operand.x +
        _arr[9] * operand.y +
        _arr[10] * operand.z
    );

    return v;
}

Mat3& Mat3::transpose() { // TODO: optimise this (do this inplace)
    std::array<float, 9> v;

    for (int r=0; r < 3; r++) {
        for (int c=0; c < 3; c++) {
            v[r * 3 + c] = _arr[c * 3 + r];
        }
    }

    _arr = v;

    return *this;
}

const float* Mat4::operator[](const int r) const { return &_arr[r * 4]; }

float* Mat4::operator[](const int r) { return &_arr[r * 4]; }

bool Mat4::operator==(const Mat4 operand) const { return (_arr == operand._arr); }; // FIXME: floating point percision

bool Mat4::operator!=(const Mat4 operand) const { return (_arr != operand._arr); }; // FIXME: floating point percision

Mat4 Mat4::operator*(const Mat4 operand) const {
    Mat4 v;

    for (int r=0; r < 4; r++) {
        for (int c=0; c < 4; c++) {
            v[r][c] = (
                _arr[r * 4] * operand[0][c] +
                _arr[r * 4 + 1] * operand[1][c] +
                _arr[r * 4 + 2] * operand[2][c] +
                _arr[r * 4 + 3] * operand[3][c]
            );
        }
    }

    return v;
}

Mat4& Mat4::operator*=(const Mat4 operand) {
    std::array<float, 16> v;

    for (int r=0; r < 4; r++) {
        for (int c=0; c < 4; c++) {
            v[r * 4 + c] = (
                _arr[r * 4] * operand[0][c] +
                _arr[r * 4 + 1] * operand[1][c] +
                _arr[r * 4 + 2] * operand[2][c] +
                _arr[r * 4 + 3] * operand[3][c]
            );
        }
    }

    _arr = v;

    return *this;
}

Tuple4 Mat4::operator*(const Tuple4 operand) const {
    Tuple4 v;

    v.x = (
        _arr[0] * operand.x +
        _arr[1] * operand.y +
        _arr[2] * operand.z +
        _arr[3] * operand.w
    );
    v.y = (
        _arr[4] * operand.x +
        _arr[5] * operand.y +
        _arr[6] * operand.z +
        _arr[7] * operand.w
    );
    v.z = (
        _arr[8] * operand.x +
        _arr[9] * operand.y +
        _arr[10] * operand.z +
        _arr[11] * operand.w
    );
    v.w = (
        _arr[12] * operand.x +
        _arr[13] * operand.y +
        _arr[14] * operand.z +
        _arr[15] * operand.w
    );

    return v;
}

Mat4& Mat4::transpose() { // TODO: optimise this (do this inplace)
    std::array<float, 16> v;

    for (int r=0; r < 4; r++) {
        for (int c=0; c < 4; c++) {
            v[r * 4 + c] = _arr[c * 4 + r];
        }
    }

    _arr = v;

    return *this;
}