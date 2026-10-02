#pragma once

#include "maths/tuple.h"


struct Ray {
    public:
    Tuple4 origin;
    Tuple4 direction;

    Tuple4 at(float t) const;

    Ray(Tuple4 _origin, Tuple4 _direction) : origin(_origin), direction(_direction) {}
};