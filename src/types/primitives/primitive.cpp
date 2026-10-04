#include "types/primitives/primitive.h"


IntersectionArray Primitive::intersect(Ray r) const {
    return IntersectionArray(); // always report no intersections, this should never be called
}

Tuple4 Primitive::normalAt(const Tuple4 p) const {
    return p;
}

Primitive& Primitive::transform(const Mat4 operand) {
    transformation *= operand;

    return *this;
}