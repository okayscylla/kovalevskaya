#pragma once

#include <cstdint>


class Colour {
    public:
    float red, green, blue;

    Colour operator+(const Colour operand) const;
    Colour operator-(const Colour operand) const;
    Colour& operator+=(const Colour operand);
    Colour& operator-=(const Colour operand);
    
    Colour operator*(const double scalar) const;
    Colour operator/(const double scalar) const;
    Colour& operator*=(const double scalar);
    Colour& operator/=(const double scalar);

    Colour operator*(const Colour operand) const; // hadamard product
    Colour& operator*=(const Colour operand); // hadamard produca

    bool operator==(const Colour operand) const;
    bool operator!=(const Colour operand) const;

    Colour negate() const;

    float magnitude() const;
    Colour& normalise();

    uint32_t toInt() const;

    Colour(float _red, float _green, float _blue) : red(_red), green(_green), blue(_blue) {}
};