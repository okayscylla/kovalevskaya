#include "maths/matrix.h"


const float* Mat2::operator[](const int r) const { return &_arr[r * 2]; }

const float* Mat2::operator[](const int r) { return &_arr[r * 2]; }

bool Mat2::operator==(const Mat2 operand) const { return (_arr == operand._arr); };

bool Mat2::operator!=(const Mat2 operand) const { return (_arr != operand._arr); };

const float* Mat3::operator[](const int r) const { return &_arr[r * 3]; }

const float* Mat3::operator[](const int r) { return &_arr[r * 3]; }

bool Mat3::operator==(const Mat3 operand) const { return (_arr == operand._arr); };

bool Mat3::operator!=(const Mat3 operand) const { return (_arr != operand._arr); };

const float* Mat4::operator[](const int r) const { return &_arr[r * 4]; }

const float* Mat4::operator[](const int r) { return &_arr[r * 4]; }

bool Mat4::operator==(const Mat4 operand) const { return (_arr == operand._arr); };

bool Mat4::operator!=(const Mat4 operand) const { return (_arr != operand._arr); };