#pragma once

#include "types/primitives/primitive.h"


class Sphere : public Primitive {
    public:
    IntersectionArray intersect(Ray r) const;
    Tuple4 normalAt(const Tuple4 p) const;

    Sphere(int _id) : Primitive(_id) {}

    ~Sphere() {}
};