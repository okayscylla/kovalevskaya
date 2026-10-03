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

TEST_CASE("translating a ray (inplace)") {
    Ray r = Ray(Point(1, 2, 3), Vector(0, 1, 0));

    r.transform(Translate(3, 4, 5));

    CHECK(r.origin == Point(4, 6, 8));
    CHECK(r.direction == Vector(0, 1, 0));
}

TEST_CASE("scaling a ray (out of place)") {
    Ray r = Ray(Point(1, 2, 3), Vector(0, 1, 0));

    Ray v = r.transformed(Scale(2, 3, 4));

    CHECK(v.origin == Point(2, 6, 12));
    CHECK(v.direction == Vector(0, 3, 0));
}