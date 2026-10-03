#include "types/primitives/misc/ray.h"


Tuple4 Ray::at(float t) const {
    return origin + direction * t;
}

Ray& Ray::transform(const Mat4 matrix) {
    origin = matrix * origin;
    direction = matrix * direction;

    return *this;
}

Ray Ray::transformed(const Mat4 matrix) const {
    Ray v = Ray(origin, direction);

    v.transform(matrix);

    return v;
}