#pragma once

#include "maths/matrix.h"
#include "maths/tuple.h"


struct Ray {
    public:
    Tuple4 origin;
    Tuple4 direction;

    Tuple4 at(float t) const;
    Ray& transform(const Mat4 matrix);
    Ray transformed(const Mat4 matrix) const;

    Ray(Tuple4 _origin, Tuple4 _direction) : origin(_origin), direction(_direction) {}
};