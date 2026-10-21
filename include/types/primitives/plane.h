#pragma once

#include "types/primitives/primitive.h"


class Plane : public Primitive {
    public:
    IntersectionArray localIntersect(Ray r) const;
    Tuple4 localNormalAt(const Tuple4 p) const;

    Plane(int _id, Material _material) : Primitive(_id, _material) {}
    Plane(int _id) : Primitive(_id) {}

    ~Plane() {}
};