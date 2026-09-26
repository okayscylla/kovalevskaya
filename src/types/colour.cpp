#include "types/colour.h"

#include "utils/macros.h"
#include "maths/constants.h"

#include <cmath>


Colour Colour::operator+(const Colour operand) const {
    return Colour(red + operand.red, green + operand.green, blue + operand.blue);
}

Colour Colour::operator-(const Colour operand) const {
    return Colour(red - operand.red, green - operand.green, blue - operand.blue);

}

Colour& Colour::operator+=(const Colour operand) {
    red += operand.red;
    green += operand.green;
    blue += operand.blue;

    return *this;
}

Colour& Colour::operator-=(const Colour operand) {
    red -= operand.red;
    green -= operand.green;
    blue -= operand.blue;

    return *this;
}

Colour Colour::operator*(const double scalar) const {
    return Colour(red * scalar, green * scalar, blue * scalar);
}

Colour Colour::operator/(const double scalar) const {
    if (notZero(scalar)) { 
        return Colour(red / scalar, green / scalar, blue / scalar);
    } else {
        return Colour(0, 0, 0);
    }
}

Colour& Colour::operator*=(const double scalar) {
    red *= scalar;
    green *= scalar;
    blue *= scalar;

    return *this;
}

Colour& Colour::operator/=(const double scalar) {
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

Colour Colour::operator*(const Colour operand) const { // hadamard product
    return Colour(red * operand.red, green * operand.green, blue * operand.blue);
}

Colour& Colour::operator*=(const Colour operand) { // hadamard product
    red *= operand.red;
    green *= operand.green;
    blue *= operand.blue;

    return *this;
}

bool Colour::operator==(const Colour operand) const {
    return (assertEqual(red, operand.red) && assertEqual(green, operand.green) && assertEqual(blue, operand.blue));
}

bool Colour::operator!=(const Colour operand) const {
    return !(assertEqual(red, operand.red) && assertEqual(green, operand.green) && assertEqual(blue, operand.blue));
}

Colour Colour::negate() const {
    return Colour(-red, -green, blue);
}

float Colour::magnitude() const {
    return std::sqrtf(red*red + green*green + blue*blue);
}

Colour& Colour::normalise() {
    float m = magnitude();

    if (notZero(m)) {
        red /= m;
        green /= m;
        blue /= m;
    }

    return *this;
}

uint32_t Colour::toInt() const {
    return (
        ((uint32_t)0xFF000000) &
        ((uint32_t)std::round(blue * 255) << 4) &
        ((uint32_t)std::round(green * 255) << 2) &
        ((uint32_t)std::round(red * 255))
    );
}