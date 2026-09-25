#include "types/colour.h"

#include "utils/macros.h"

#include <cmath>


Color Color::operator+(const Color operand) const {
    return Color(red + operand.red, green + operand.green, blue + operand.blue);
}

Color Color::operator-(const Color operand) const {
    return Color(red - operand.red, green - operand.green, blue - operand.blue);

}

Color& Color::operator+=(const Color operand) {
    red += operand.red;
    green += operand.green;
    blue += operand.blue;

    return *this;
}

Color& Color::operator-=(const Color operand) {
    red -= operand.red;
    green -= operand.green;
    blue -= operand.blue;

    return *this;
}

Color Color::operator*(const double scalar) const {
    return Color(red * scalar, green * scalar, blue * scalar);
}

Color Color::operator/(const double scalar) const {
    if (notZero(scalar)) { 
        return Color(red / scalar, green / scalar, blue / scalar);
    } else {
        return Color(0, 0, 0);
    }
}

Color& Color::operator*=(const double scalar) {
    red *= scalar;
    green *= scalar;
    blue *= scalar;

    return *this;
}

Color& Color::operator/=(const double scalar) {
    if (notZero(scalar)) {
        red /= scalar;
        green /= scalar;
        blue /= scalar;
    } else {
        red = 0;
        green = 0;
        blue = 0;
    }

    return *this;
}

Color Color::operator*(const Color operand) const { // hadamard product
    return Color(red * operand.red, green * operand.green, blue * operand.blue);
}

Color& Color::operator*=(const Color operand) { // hadamard product
    red *= operand.red;
    green *= operand.green;
    blue *= operand.blue;

    return *this;
}

bool Color::operator==(const Color operand) const {
    return (assertEqual(red, operand.red) && assertEqual(green, operand.green) && assertEqual(blue, operand.blue));
}

bool Color::operator!=(const Color operand) const {
    return !(assertEqual(red, operand.red) && assertEqual(green, operand.green) && assertEqual(blue, operand.blue));
}

Color Color::negate() const {
    return Color(-red, -green, blue);
}

float Color::magnitude() const {
    return std::sqrtf(red*red + green*green + blue*blue);
}

Color& Color::normalise() {
    float m = magnitude();

    if (notZero(m)) {
        red /= m;
        green /= m;
        blue /= m;
    }

    return *this;
}