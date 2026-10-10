#pragma once

#include "maths/tuple.h"
#include "types/basic/colour.h"


class Light {
    public:
    Tuple4 position;
    Colour intensity;

    Light(Tuple4 _p, Colour _i) : position(_p), intensity(_i) {}
};

class PointLight : Light {
    public:
    PointLight(Tuple4 pos) : Light(pos, Colour(1,1,1)) {}
    PointLight(Tuple4 pos, Colour _i) : Light(pos, _i) {}
};