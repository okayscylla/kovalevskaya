#include "types/primitives/plane.h"

#include "utils/macros.h"

#include <cmath>


IntersectionArray Plane::localIntersect(Ray r) const {
    if (isZero(r.direction.y)) { // all planes xz before being translated, only need to check y
        return IntersectionArray();
    }

    int t = -ray.origin.y / ray.direction.y;

    return IntersectionArray(
        {Intersection(t, this)}
    );
}

Tuple4 Plane::localNormalAt(const Tuple4 p) const {
    return Vector(0,1,0); // lmao
}