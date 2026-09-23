#pragma once


class Color {
    public:
    float red, green, blue;

    Color operator+(const Color operand) const;
    Color operator-(const Color operand) const;
    Color& operator+=(const Color operand);
    Color& operator-=(const Color operand);
    
    Color operator*(const double scalar) const;
    Color operator/(const double scalar) const;
    Color& operator*=(const double scalar);
    Color& operator/=(const double scalar);

    Color operator*(const Color operand) const;
    Color& operator*=(const Color operand);

    bool operator==(const Color operand) const;
    bool operator!=(const Color operand) const;

    Color negate() const;

    float magnitude() const;
    Color& normalise();

    

    Color(float _red, float _green, float _blue) : red(_red), green(_green), blue(_blue) {}
};