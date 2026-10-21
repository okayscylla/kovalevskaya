#include "types/primitives/primitive.h"


IntersectionArray Primitive::intersect(Ray r) const {
    Ray local_ray = ray.transform(transformation.inverse());

    return localIntersect(local_ray);
}

Tuple4 Primitive::normalAt(const Tuple4 p, bool world_space) const {
    Tuple4 local_point = transformation.inverse() * p;
    Tuple4 local_normal = localNormalAt(local_point);

    if (world_space) {
        Tuple4 world_normal = transformation.invert().transpose() * local_normal;
        world_normal.w = 0;

        return world_normal.normalise(); // should this be not inplace?
    } else {
        return local_normal.normalise(); // should this be not inplace?
    }
}

Primitive& Primitive::transform(const Mat4 operand) {
    transformation *= operand;

    return *this;
}

Primitive& Primitive::init(int _id) {
    id = _id;

    return *this;
}

IntersectionArray localIntersect(Ray r) const {
    return IntersectionArray();
}

Tuple4 Primitive::localNormalAt(const Tuple4 p) const {
    Tuple4 local_normal = local_point - Point(0, 0, 0); // FIXME: see above

    return local_normal;
}