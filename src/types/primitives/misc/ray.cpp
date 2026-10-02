#include "types/primitives/misc/ray.h"


Tuple4 Ray::at(float t) const {
    return origin + direction * t;
}