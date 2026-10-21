#pragma once

#include "types/primitives/primitive.h"


class Sphere : public Primitive {
    public:
    IntersectionArray localIntersect(Ray r) const;
    Tuple4 localNormalAt(const Tuple4 p) const;

    Sphere(int _id, Material _material) : Primitive(_id, _material) {}
    Sphere(int _id) : Primitive(_id) {}

    ~Sphere() {}
};