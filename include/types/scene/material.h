#pragma once

#include "types/basic/colour.h"


struct Material {
    public:
    const Colour colour;
    const float ambient, diffuse, specular, shininess;

    bool operator==(const Material operand) const;
    bool operator!=(const Material operand) const;

    Material(Colour col, float am, float di, float sp, float sh) : colour(col), ambient(am), diffuse(di), specular(sp), shininess(sh) {}
    Material(Colour col) : colour(col), ambient(0.1f), diffuse(0.9f), specular(0.9f), shininess(200.f) {} // default material :3
    Material() : colour(1,1,1), ambient(0.1f), diffuse(0.9f), specular(0.9f), shininess(200.f) {} // default colour, default material :3
};