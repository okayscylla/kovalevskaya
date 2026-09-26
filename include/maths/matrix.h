#pragma once

#include <cstdlib>
#include <array>


class Mat2 {
    public:
    const float* operator[](const int r) const;
    const float* operator[](const int r);

    bool operator==(const Mat2 operand) const;
    bool operator!=(const Mat2 operand) const;

    Mat2(std::array<float, 4> val) : _arr(val) {}

    private:
    std::array<float, 4> _arr; // row, col
};

class Mat3 {
    public:
    const float* operator[](const int r) const;
    const float* operator[](const int r);

    bool operator==(const Mat3 operand) const;
    bool operator!=(const Mat3 operand) const;

    Mat3(std::array<float, 9> val) : _arr(val) {}

    private:
    std::array<float, 9> _arr; // row, col
};

class Mat4 {
    public:
    const float* operator[](const int r) const;
    const float* operator[](const int r);

    bool operator==(const Mat4 operand) const;
    bool operator!=(const Mat4 operand) const;

    Mat4(std::array<float, 16> val) : _arr(val) {}

    private:
    std::array<float, 16> _arr; // row, col
};