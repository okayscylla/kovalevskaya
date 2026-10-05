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

TEST_CASE("intersecting a scaled sphere with a ray") {
    Ray r = Ray(Point(0, 0, -5), Vector(0, 0, 1));
    Sphere s = Sphere(67);

    s.transform(Scale(2, 2, 2));

    IntersectionArray intersections = s.intersect(r);

    CHECK(intersections.size() == 2);
    CHECK(intersections[0].t == 3.f);
    CHECK(intersections[1].t == 7.f);
}

TEST_CASE("finding a normal on a sphere") {
    Sphere s = Sphere(67);
    Tuple4 n = s.normalAt(Point(std::sqrtf(3) / 3, std::sqrtf(3) / 3, std::sqrtf(3) / 3), false);

    CHECK(n == Vector(std::sqrtf(3) / 3, std::sqrtf(3) / 3, std::sqrtf(3) / 3));
}

TEST_CASE("finding a normal on a sphere (axis aligned)") {
    Sphere s = Sphere(67);
    Tuple4 n = s.normalAt(Point(0, 0, 1), false);

    CHECK(n == Vector(0, 0, 1));
}

TEST_CASE("normals are normalised (wuh)") {
    Sphere s = Sphere(67);
    Tuple4 n = s.normalAt(Point(std::sqrtf(3) / 3, std::sqrtf(3) / 3, std::sqrtf(3) / 3), false);

    CHECK(n == n.normalise());
}

TEST_CASE("normals on a translated sphere") {
    Sphere s = Sphere(67);
    s.transform(Translate(0, 1, 0));
    Tuple4 n = s.normalAt(Point(0, 1.70711, -0.70711));

    CHECK(n == Vector(0, 0.70711, -0.70711));
}

TEST_CASE("normals on a transformed sphere") { // FIXME: make this test work :3
    Sphere s = Sphere(67);
    s.transform(Scale(1, 0.5, 1) * RotateZ(PI / 5));
    Tuple4 n = s.normalAt(Point(0, std::sqrtf(2) / 2, -(std::sqrtf(3) / 3)));

    CHECK(n == Vector(0, 0.97014, -0.24254));
}