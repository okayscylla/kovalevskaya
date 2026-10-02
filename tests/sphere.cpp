#include "misc/base.h"

#include "types/primitives/sphere.h"


TEST_CASE("ray-sphere intersections (2 intersections)") {
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere(0);

    IntersectionArray intersections = s.intersect(r);

    CHECK(s.id == 0);
    CHECK(intersections.size() == 2);
    CHECK(intersections[0].object == &s);
    CHECK(intersections[1].object == &s);
    CHECK(intersections[0].t == 4.0f);
    CHECK(intersections[1].t == 6.0f);
}

TEST_CASE("ray-sphere intersections (1 intersection tangent to the sphere)") {
    Ray r = Ray(Point(0, 1, -5), Vector(0, 0, 1));
    Sphere s = Sphere(1);

    IntersectionArray intersections = s.intersect(r);

    CHECK(s.id == 1);
    CHECK(intersections.size() == 2); // this is not correct but simplifies some things
    CHECK(intersections[0].object == &s);
    CHECK(intersections[1].object == &s);
    CHECK(intersections[0].t == 5.0f);
    CHECK(intersections[1].t == 5.0f);

}

TEST_CASE("ray-sphere intersections (0 intersections)") {
    Ray r = Ray(Point(0, 2, -5), Vector(0, 0, 1));
    Sphere s = Sphere(2);

    IntersectionArray intersections = s.intersect(r);

    CHECK(s.id == 2);
    CHECK(intersections.size() == 0);
}

TEST_CASE("ray-sphere intersections (2 intersection from ray inside the sphere)") {
    Ray r = Ray(Point(0, 0, 0), Vector(0, 0, 1));
    Sphere s = Sphere(3);

    IntersectionArray intersections = s.intersect(r);

    CHECK(s.id == 3);
    CHECK(intersections.size() == 2);
    CHECK(intersections[0].object == &s);
    CHECK(intersections[1].object == &s);
    CHECK(intersections[0].t == -1.0f);
    CHECK(intersections[1].t == 1.0f);
}

TEST_CASE("ray-sphere intersections (2 intersection from ray in front of the sphere)") {
    Ray r = Ray(Point(0, 0, 5), Vector(0, 0, 1));
    Sphere s = Sphere(67); // hehe 67

    IntersectionArray intersections = s.intersect(r);

    CHECK(s.id == 67);
    CHECK(intersections.size() == 2);
    CHECK(intersections[0].object == &s);
    CHECK(intersections[1].object == &s);
    CHECK(intersections[0].t == -6.0f);
    CHECK(intersections[1].t == -4.0f);
}