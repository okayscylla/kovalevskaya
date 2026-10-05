#include "maths/matrix.h"

#include "maths/constants.h"
#include "utils/macros.h"

#include <cmath>


const float* Mat2::operator[](const int r) const {
    return &_arr[r * 2];
}

float* Mat2::operator[](const int r) {
    return &_arr[r * 2];
}

bool Mat2::operator==(const Mat2 operand) const { // FIXME: floating point percision
    return (_arr == operand._arr);
};

bool Mat2::operator!=(const Mat2 operand) const { // FIXME: floating point percision
    return (_arr != operand._arr);
};

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

Mat2& Mat2::transpose() { // TODO: optimise this (do this inplace)
    std::array<float, 4> v;

    for (int r=0; r < 2; r++) { // TODO: skip fancy loop, just swap manually
        for (int c=0; c < 2; c++) {
            v[r * 2 + c] = _arr[c * 2 + r];
        }
    }

    _arr = v;

    return *this;
}

float Mat2::determinant() const {
    return _arr[0] * _arr[3] - _arr[1] * _arr[2];
}

const float* Mat3::operator[](const int r) const {
    return &_arr[r * 3];
}

float* Mat3::operator[](const int r) {
    return &_arr[r * 3];
}

bool Mat3::operator==(const Mat3 operand) const { // FIXME: floating point percision
    return (_arr == operand._arr);
};

bool Mat3::operator!=(const Mat3 operand) const { // FIXME: floating point percision
    return (_arr != operand._arr);
};

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

Mat2 Mat3::submatrix(int r, int c) const {
    std::array<float, 4> v; // TODO: replace this with just a mat2 and do inplace

    int k = 0;

    for (int i=0; i < 3; i++) {
        for (int j=0; j < 3; j++) {
            if ((i != r) && (j != c)) {
                v[k] = _arr[i * 3 + j];
                k++;
            }
        }
    }

    return Mat2(v);
}

float Mat3::determinant() const { // TODO: pick the smallest row / col to reduce required computations?
    float v = 0;

    for (int i=0; i < 3; i++) {
        v += _arr[i] * cofactor(0, i);
    }

    return v;
}

float Mat3::minor(int r, int c) const {
    return submatrix(r, c).determinant();
}

float Mat3::cofactor(int r, int c) const {
    int sign;

    if ((r * 3 + c) % 2 == 0) {
        sign = 1;
    } else {
        sign = -1;
    }

    return minor(r, c) * sign;
}

const float* Mat4::operator[](const int r) const {
    return &_arr[r * 4];
}

float* Mat4::operator[](const int r) {
    return &_arr[r * 4];
}

bool Mat4::operator==(const Mat4 operand) const { // TODO: optimise this?
    for (int r=0; r < 4; r++) {
        for (int c=0; c < 4; c++) {
            if (notZero(_arr[r * 4 + c] - operand[r][c])) {
                return false;
            }
        }
    }

    return true;
};

bool Mat4::operator!=(const Mat4 operand) const { // TODO: optimise this?
    for (int r=0; r < 4; r++) {
        for (int c=0; c < 4; c++) {
            if (notZero(_arr[r * 4 + c] - operand[r][c])) {
                return true;
            }
        }
    }

    return false;};

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

Mat4 Mat4::inverse() const {
    Mat4 v;

    if (!invertible()) {
        v._arr = _arr;
        return v; // fail quietly, maybe a bad idea?
    }

    for (int r=0; r < 4; r++) {
        for (int c=0; c < 4; c++) {
            v[c][r] = cofactor(r, c) / determinant();
        }
    }

    return v;
}

Mat4& Mat4::invert() {
    if (!invertible()) {
        return *this; // fail quietly, maybe a bad idea?
    }

    std::array<float, 16> v;

    for (int r=0; r < 4; r++) {
        for (int c=0; c < 4; c++) {
            v[c * 4 + r] = cofactor(r, c) / determinant();
        }
    }

    _arr = v;

    return *this;
}

Mat3 Mat4::submatrix(int r, int c) const {
    std::array<float, 9> v; // TODO: replace this with just a mat2 and do inplace

    int k = 0;

    for (int i=0; i < 4; i++) {
        for (int j=0; j < 4; j++) {
            if ((i != r) && (j != c)) {
                v[k] = _arr[i * 4 + j];
                k++;
            }
        }
    }

    return Mat3(v);
}

float Mat4::determinant() const { // TODO: pick the smallest row / col to reduce required computations?
    float v = 0;

    for (int i=0; i < 4; i++) {
        v += _arr[i] * cofactor(0, i);
    }

    return v;
}

float Mat4::minor(int r, int c) const {
    return submatrix(r, c).determinant();
}

float Mat4::cofactor(int r, int c) const {
    int sign;

    if ((c - (r % 2)) % 2 == 0) { // TODO: find a better solution than this mess?
        sign = 1;
    } else {
        sign = -1;
    }

    return minor(r, c) * sign;
}

bool Mat4::invertible() const {
    return (notZero(determinant()));
}