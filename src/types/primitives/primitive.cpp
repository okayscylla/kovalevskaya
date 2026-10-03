#include "types/primitives/primitive.h"


Primitive& Primitive::transform(const Mat4 operand) {
    transformation *= operand;

    return *this;
}

IntersectionArray Primitive::intersect(Ray r) const {
    return IntersectionArray(); // always report no intersections, this should never be called
}