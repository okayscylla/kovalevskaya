#pragma once


class Tuple4 {
    public:
    float x, y, z, w;

    Tuple4 operator+(const Tuple4 operand) const;
    Tuple4 operator-(const Tuple4 operand) const;
    Tuple4& operator+=(const Tuple4 operand);
    Tuple4& operator-=(const Tuple4 operand);
    
    Tuple4 operator*(const double scalar) const;
    Tuple4 operator/(const double scalar) const;
    Tuple4& operator*=(const double scalar);
    Tuple4& operator/=(const double scalar);

    bool operator==(const Tuple4 operand) const;
    bool operator!=(const Tuple4 operand) const;
    
    Tuple4 negate() const;
    Tuple4 unitVector() const;

    bool isPoint() const;
    bool isVector() const;

    float magnitude() const;
    Tuple4& normalise();
    
    float dot(const Tuple4 operand) const;
    Tuple4 cross(const Tuple4 operand) const;

    Tuple4(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w) {}
};

class Tuple3 {
    public:
    float x, y, z;

    Tuple3 operator+(const Tuple3 operand) const;
    Tuple3 operator-(const Tuple3 operand) const;
    Tuple3& operator+=(const Tuple3 operand);
    Tuple3& operator-=(const Tuple3 operand);
    
    Tuple3 operator*(const double scalar) const;
    Tuple3 operator/(const double scalar) const;
    Tuple3& operator*=(const double scalar);
    Tuple3& operator/=(const double scalar);

    bool operator==(const Tuple3 operand) const;
    bool operator!=(const Tuple3 operand) const;
    
    Tuple3 negate() const;
    Tuple3 unitVector() const;

    float magnitude() const;
    Tuple3& normalise();
    
    float dot(const Tuple3 operand) const;
    Tuple3 cross(const Tuple3 operand) const;

    Tuple3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};

#define Point(x, y, z)      Tuple4(x, y, z, 1.0)
#define Vector(x, y, z)     Tuple4(x, y, z, 0.0)