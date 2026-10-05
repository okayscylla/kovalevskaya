#include "types/primitives/sphere.h"

#include "maths/constants.h"
#include "utils/macros.h"

#include <cmath>


IntersectionArray Sphere::intersect(Ray r) const {
    r = r.transform(transformation.inverse());

    Tuple4 sphere_ray = (r.origin - Point(0, 0, 0)); // FIXME: add support for centers other than the world origin

    float a = r.direction.dot(r.direction);
    float b = 2 * r.direction.dot(sphere_ray);
    float c = sphere_ray.dot(sphere_ray) - 1;

    float discriminant = b*b - (4 * a * c);

    if (discriminant < (-EPSILON)) {
        return IntersectionArray();
    }

    Intersection t1 = Intersection(((-0.5f * (b - (std::sqrtf(discriminant)))) / a), this);
    Intersection t2 = Intersection(((-0.5f * (b + (std::sqrtf(discriminant)))) / a), this);

    if (notZero(t1.t - t2.t) && t1.t > t2.t) {
        return IntersectionArray({t2, t1});
    }

    return IntersectionArray({t1, t2});
}

Tuple4 Sphere::normalAt(const Tuple4 p, bool world_space) const {
    Tuple4 local_point = transformation.inverse() * p;
    Tuple4 local_normal = local_point - Point(0, 0, 0); // FIXME: see above

    if (world_space) {
        Tuple4 world_normal = transformation.inverse().transpose() * local_normal;
        world_normal.w = 0; // sketchy hack :peepoScared:

        return world_normal.normalise();
    } else {
        return local_normal.normalise();
    }
}