#include "types/primitives/plane.h"

#include "utils/macros.h"

#include <cmath>


IntersectionArray Plane::localIntersect(Ray r) const {
    if (isZero(r.direction.y)) { // all planes xz before being translated, only need to check y
        return IntersectionArray();
    }

    int t = -r.origin.y / r.direction.y;

    return IntersectionArray(
        {Intersection(t, const_cast<Plane*>(this))} // this is unsafe
    );
}

Tuple4 Plane::localNormalAt(const Tuple4 p) const {
    return Vector(0,1,0); // lmao
}