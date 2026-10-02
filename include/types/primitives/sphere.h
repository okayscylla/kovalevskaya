#pragma once

#include "types/primitives/primitive.h"


class Sphere : public Primitive {
    public:
    IntersectionArray intersect(Ray r) const;

    Sphere(int _id) : Primitive(_id) {}
};