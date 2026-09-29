#pragma once

#include "maths/tuple.h"

#include <array>


class Mat2 {
    public:
    const float* operator[](const int r) const;
    float* operator[](const int r);

    bool operator==(const Mat2 operand) const;
    bool operator!=(const Mat2 operand) const;

    Mat2 operator*(const Mat2 operand) const;
    Mat2& operator*=(const Mat2 operand); // TODO: implement Tuple2 and add multiplication by tuples to Mat2

    Mat2(std::array<float, 4> val) : _arr(val) {}
    Mat2() : _arr({
        1,0,
        0,1
    }) {} // identity matrix :3

    private:
    std::array<float, 4> _arr; // row, col
};

class Mat3 {
    public:
    const float* operator[](const int r) const;
    float* operator[](const int r);

    bool operator==(const Mat3 operand) const;
    bool operator!=(const Mat3 operand) const;

    Mat3 operator*(const Mat3 operand) const;
    Mat3& operator*=(const Mat3 operand);

    Tuple3 operator*(const Tuple3 operand) const;

    Mat3(std::array<float, 9> val) : _arr(val) {}
    Mat3() : _arr({
        1,0,0,
        0,1,0,
        0,0,1
    }) {} // identity matrix :3

    private:
    std::array<float, 9> _arr; // row, col
};

class Mat4 {
    public:
    const float* operator[](const int r) const;
    float* operator[](const int r);

    bool operator==(const Mat4 operand) const;
    bool operator!=(const Mat4 operand) const;

    Mat4 operator*(const Mat4 operand) const;
    Mat4& operator*=(const Mat4 operand);

    Tuple4 operator*(const Tuple4 operand) const;

    Mat4(std::array<float, 16> val) : _arr(val) {}
    Mat4() : _arr({
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    }) {}  // identity matrix :3

    private:
    std::array<float, 16> _arr; // row, col
};