#include "misc/base.h"

#include "types/primitives/sphere.h"


TEST_CASE("adding two intersection arrays") {
    Sphere s = Sphere(0);
    IntersectionArray a = IntersectionArray({Intersection(1, &s), Intersection(2, &s)});
    IntersectionArray b = IntersectionArray({Intersection(3, &s), Intersection(4, &s)});
    IntersectionArray c = a + b;

    CHECK(c[0].t == Intersection(1, &s).t);
    CHECK(c[1].t == Intersection(2, &s).t);
    CHECK(c[2].t == Intersection(3, &s).t);
    CHECK(c[3].t == Intersection(4, &s).t);
}

TEST_CASE("adding two intersection arrays (inplace)") {
    Sphere s = Sphere(0);
    IntersectionArray a = IntersectionArray({Intersection(1, &s), Intersection(2, &s)});
    IntersectionArray b = IntersectionArray({Intersection(3, &s), Intersection(4, &s)});
    a += b;

    CHECK(a[0].t == Intersection(1, &s).t);
    CHECK(a[1].t == Intersection(2, &s).t);
    CHECK(a[2].t == Intersection(3, &s).t);
    CHECK(a[3].t == Intersection(4, &s).t);
}

TEST_CASE("search for a hit (valid hit exists)") {
    Sphere s = Sphere(67);

    IntersectionArray a = IntersectionArray({
        Intersection(-1, &s),
        Intersection(1, &s),
        Intersection(0.1, &s),
        Intersection(0.5, &s)
    });

    Intersection i = a.findHit();

    CHECK(i.null == false);
    CHECK(assertEqual(i.t, 0.1));
    CHECK(i.object == &s);
}

TEST_CASE("searching for a hit (no valid hits)") {
    Sphere s = Sphere(67);

    IntersectionArray a = IntersectionArray({
        Intersection(-1, &s),
        Intersection(-1, &s),
        Intersection(-0.1, &s),
        Intersection(-0.5, &s)
    });

    Intersection i = a.findHit();

    CHECK(i.null == true);
}