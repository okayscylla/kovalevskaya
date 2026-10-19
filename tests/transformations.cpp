#include "misc/base.h"

#include "maths/matrix.h"
#include "utils/helpers.h"
#include <cmath>


TEST_CASE("multiplying by a transformation matrix") {
    Tuple4 a = Point(-3, 4, 5);
    Mat4 b = Translate(5, -3, 2);

    CHECK(b * a == Point(2, 1, 7));
}

TEST_CASE("multiplying by the inverse of a transformation matrix") {
    Tuple4 a = Point(-3, 4, 5);
    Mat4 b = Translate(5, -3, 2).invert();

    CHECK(b * a == Point(-8, 7, 3));
}

TEST_CASE("translation doesn't affect vectors") {
    Tuple4 a = Vector(-3, 4, 5);
    Mat4 b = Translate(5, -3, 2);

    CHECK(b * a == a);
}

TEST_CASE("multiplying a point by a scaling matrix") {
    Tuple4 a = Point(-4, 6, 8);
    Mat4 b = Scale(2, 3, 4);

    CHECK(b * a == Point(-8, 18, 32));
}

TEST_CASE("multiplying a vector by a scaling matrix") {
    Tuple4 a = Vector(-4, 6, 8);
    Mat4 b = Scale(2, 3, 4);

    CHECK(b * a == Vector(-8, 18, 32));
}

TEST_CASE("multiplying a vector by the inverse of a scaling matrix") {
    Tuple4 a = Vector(-4, 6, 8);
    Mat4 b = Scale(2, 3, 4).invert();

    CHECK(b * a == Vector(-2, 2, 2));
}

TEST_CASE("reflection is scaling by a negative value") {
    Tuple4 a = Point(2, 3, 4);
    Mat4 b = Scale(-1, 1, 1);

    CHECK(b * a == Point(-2, 3, 4));
}

TEST_CASE("rotating a point around the x-axis") {
    Tuple4 a = Point(0, 1, 0);
    Mat4 b = RotateX(PI / 4); // 45 degrees
    Mat4 c = RotateX(PI / 2); // 90 degrees

    CHECK(b * a == Point(0, std::sqrtf(2) / 2, std::sqrtf(2) / 2)); // yay unit circle !!
    CHECK(c * a == Point(0, 0, 1));
}

TEST_CASE("the inverse of the thingy rotates it the other way") {
    Tuple4 a = Point(0, 1, 0);
    Mat4 b = RotateX(PI / 4).invert(); // -45 (methinks) degrees

    CHECK(b * a == Point(0, std::sqrtf(2) / 2, -(std::sqrtf(2) / 2))); // yay unit circle !!
}

TEST_CASE("rotating a point around the y-axis") {
    Tuple4 a = Point(0, 0, 1);
    Mat4 b = RotateY(PI / 4); // 45 degrees
    Mat4 c = RotateY(PI / 2); // 90 degrees

    CHECK(b * a == Point(std::sqrtf(2) / 2, 0, std::sqrtf(2) / 2)); // yay unit circle !!
    CHECK(c * a == Point(1, 0, 0));
}

TEST_CASE("rotating a point around the z-axis") {
    Tuple4 a = Point(0, 1, 0);
    Mat4 b = RotateZ(PI / 4); // 45 degrees
    Mat4 c = RotateZ(PI / 2); // 90 degrees

    CHECK(b * a == Point(-(std::sqrtf(2) / 2), std::sqrtf(2) / 2, 0)); // yay unit circle !!
    CHECK(c * a == Point(-1, 0, 0));
}

TEST_CASE("shearing x in proportion to y") { // TODO: implement more tests?
    Tuple4 a = Point(2, 3, 4);
    Mat4 b = Shear(1, 0, 0, 0, 0, 0);

    CHECK(b * a == Point(5, 3, 4));
}

TEST_CASE("chaining transformations") { // PLEASE work :3
    Tuple4 a = Point(1, 0, 1);
    Mat4 b = RotateX(PI / 2);
    Mat4 c = Scale(5, 5, 5);
    Mat4 d = Translate(10, 5, 7);

    CHECK((d * c * b) * a == Point(15, 0, 7));
}

TEST_CASE("transformation matrix for default oreintation") {
    Mat4 a = ViewTransform(
        Point(0,0,0),
        Point(0,0,-1),
        Vector(0,1,0)
    );

    CHECK(a == Mat4()); // identity matrix
}

TEST_CASE("view transformation matrix in pos z direction") {
    Mat4 a = ViewTransform(
        Point(0,0,0),
        Point(0,0,1),
        Vector(0,1,0)
    );

    CHECK(a == Scale(-1,1,-1));
}

TEST_CASE("view translation moving the world") {
    Mat4 a = ViewTransform(
        Point(0,0,8),
        Point(0,0,0),
        Vector(0,1,0)
    );

    CHECK(a == Translate(0,0,-8));
}

TEST_CASE("idk just a random view transformation") {
    Mat4 a = ViewTransform(
        Point(1,3,2),
        Point(4,-2,8),
        Vector(1,1,0)
    );

    CHECK(a == Mat4({
        -0.50709,0.50709,0.67612,-2.36643,
        0.76772,0.60609,0.12122,-2.82843,
        -0.35857,0.59761,-0.71714,0.00000,
        0.00000,0.00000,0.00000,1.00000
    }));
}