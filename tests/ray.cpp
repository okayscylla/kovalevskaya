#include "misc/base.h"

#include "types/primitives/misc/ray.h"


TEST_CASE("creating a ray yay") { // hey that rhymes!
    Tuple4 origin = Point(1, 2, 3);
    Tuple4 direction = Vector(4, 5, 6);

    Ray r = Ray(origin, direction);

    CHECK(r.origin == origin);
    CHECK(r.direction == direction);
}

TEST_CASE("computing a point at a distance along a ray yay") {
    Ray r = Ray(Point(2, 3, 4), Vector(1, 0, 0));

    CHECK(r.at(0) == Point(2, 3, 4));
    CHECK(r.at(1) == Point(3, 3, 4));
    CHECK(r.at(-1) == Point(1, 3, 4)); // this makes total sense dont think abt it too hard
    CHECK(r.at(2.5) == Point(4.5, 3, 4));
}