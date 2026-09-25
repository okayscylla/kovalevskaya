#include "maths/tuple.h"

#include "utils/macros.h"

#include <cmath>


Tuple4 Tuple4::operator+(const Tuple4 operand) const {
    return Tuple4(x + operand.x, y + operand.y, z + operand.z, w + operand.w);
}

Tuple4 Tuple4::operator-(const Tuple4 operand) const {
    return Tuple4(x - operand.x, y - operand.y, z - operand.z, w - operand.w);
}

Tuple4& Tuple4::operator+=(const Tuple4 operand) {
    x += operand.x;
    y += operand.y;
    z += operand.z;
    w += operand.w;

    return *this;
}

Tuple4& Tuple4::operator-=(const Tuple4 operand) {
    x -= operand.x;
    y -= operand.y;
    z -= operand.z;
    w -= operand.w;

    return *this;
}

Tuple4 Tuple4::operator*(const double scalar) const {
    return Tuple4(x * scalar, y * scalar, z * scalar, w * scalar);
}

Tuple4 Tuple4::operator/(const double scalar) const {
    if (notZero(scalar)) { 
        return Tuple4(x / scalar, y / scalar, z / scalar, w / scalar);
    } else {
        return Tuple4(0, 0, 0, 0);
    }
}

Tuple4& Tuple4::operator*=(const double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    w *= scalar;

    return *this;
}

Tuple4& Tuple4::operator/=(const double scalar) {
    if (notZero(scalar)) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        w /= scalar;
    } else {
        x = 0;
        y = 0;
        z = 0;
        w = 0;
    }

    return *this;
}

bool Tuple4::operator==(const Tuple4 operand) const {
    return (assertEqual(x, operand.x) && assertEqual(y, operand.y) && assertEqual(z, operand.z) && assertEqual(w, operand.w));
}

bool Tuple4::operator!=(const Tuple4 operand) const {
    return !(assertEqual(x, operand.x) && assertEqual(y, operand.y) && assertEqual(z, operand.z) && assertEqual(w, operand.w));
}

Tuple4 Tuple4::negate() const {
    return Tuple4(-x, -y, -z, -w);
}

Tuple4 Tuple4::unitVector() const {
    float m = magnitude();

    if (notZero(m)) {
        return Tuple4(x / m, y / m, z / m, 0); // w=0 means vector
    }

    return Tuple4(0, 0, 0, 0);
}

bool Tuple4::isPoint() const {
    return assertEqual(w, 1.0);
}

bool Tuple4::isVector() const {
    return assertEqual(w, 0.0);
}

float Tuple4::magnitude() const {
    return std::sqrtf(x*x + y*y + z*z + w*w);
}

Tuple4& Tuple4::normalise() {
    float m = magnitude();

    if (notZero(m)) {
        x /= m;
        y /= m;
        z /= m;
    } // no w since vectors have w=0 (and who tf is normalising a point)

    return *this;
}

float Tuple4::dot(const Tuple4 operand) const {
    return (
        x * operand.x +
        y * operand.y +
        z * operand.z
    ); // no w component since the dot product only makes sense for vectors (w=0)
}

Tuple4 Tuple4::cross(const Tuple4 operand) const {
    return Vector(
        y * operand.z - z * operand.y,
        z * operand.x - x * operand.z,
        x * operand.y - y * operand.x
    );
}

Tuple3 Tuple3::operator+(const Tuple3 operand) const {
    return Tuple3(x + operand.x, y + operand.y, z + operand.z);
}

Tuple3 Tuple3::operator-(const Tuple3 operand) const {
    return Tuple3(x - operand.x, y - operand.y, z - operand.z);

}

Tuple3& Tuple3::operator+=(const Tuple3 operand) {
    x += operand.x;
    y += operand.y;
    z += operand.z;

    return *this;
}

Tuple3& Tuple3::operator-=(const Tuple3 operand) {
    x -= operand.x;
    y -= operand.y;
    z -= operand.z;

    return *this;
}

Tuple3 Tuple3::operator*(const double scalar) const {
    return Tuple3(x * scalar, y * scalar, z * scalar);
}

Tuple3 Tuple3::operator/(const double scalar) const {
    if (notZero(scalar)) { 
        return Tuple3(x * scalar, y * scalar, z * scalar);
    } else {
        return Tuple3(0, 0, 0);
    }
}

Tuple3& Tuple3::operator*=(const double scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;

    return *this;
}

Tuple3& Tuple3::operator/=(const double scalar) {
    if (notZero(scalar)) {
        x /= scalar;
        y /= scalar;
        z /= scalar;
    } else {
        x = 0;
        y = 0;
        z = 0;
    }

    return *this;
}

bool Tuple3::operator==(const Tuple3 operand) const {
    return (assertEqual(x, operand.x) && assertEqual(y, operand.y) && assertEqual(z, operand.z));
}

bool Tuple3::operator!=(const Tuple3 operand) const {
    return !(assertEqual(x, operand.x) && assertEqual(y, operand.y) && assertEqual(z, operand.z));
}

Tuple3 Tuple3::negate() const {
    return Tuple3(-x, -y, -z);
}

Tuple3 Tuple3::unitVector() const {
    float m = magnitude();

    if (notZero(m)) {
        return Tuple3(x / m, y / m, z / m);
    }

    return Tuple3(0, 0, 0);
}

float Tuple3::magnitude() const {
    return std::sqrtf(x*x + y*y + z*z);
}

Tuple3& Tuple3::normalise() {
    float m = magnitude();

    if (notZero(m)) {
        x /= m;
        y /= m;
        z /= m;
    }

    return *this;
}

float Tuple3::dot(const Tuple3 operand) const {
    return (
        x * operand.x +
        y * operand.y +
        z * operand.z
    );
}

Tuple3 Tuple3::cross(const Tuple3 operand) const {
    return Tuple3(
        y * operand.z - z * operand.y,
        z * operand.x - x * operand.z,
        x * operand.y - y * operand.x
    );
}