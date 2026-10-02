#include "misc/base.h"

#include "maths/matrix.h"
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