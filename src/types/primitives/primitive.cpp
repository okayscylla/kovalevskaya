#include "types/primitives/primitive.h"


IntersectionArray Primitive::intersect(Ray r) const {
    return IntersectionArray({}); // always report no intersections, this should never be called
}