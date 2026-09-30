#include "misc/base.h"

#include "maths/matrix.h"


TEST_CASE("multiplying by a transformation matrix") {
    Tuple4 a = Point(-3, 4, 5);
    Mat4 b = Translation(5, -3, 2);

    CHECK(b * a == Point(2, 1, 7));
}

TEST_CASE("multiplying by the inverse of a transformation matrix") {
    Tuple4 a = Point(-3, 4, 5);
    Mat4 b = Translation(5, -3, 2).invert();

    CHECK(b * a == Point(-8, 7, 3));
}

TEST_CASE("translation doesn't affect vectors") {
    Tuple4 a = Vector(-3, 4, 5);
    Mat4 b = Translation(5, -3, 2);

    CHECK(b * a == a);
}

TEST_CASE("multiplying a point by a scaling matrix") {
    Tuple4 a = Point(-4, 6, 8);
    Mat4 b = Scaling(2, 3, 4);

    CHECK(b * a == Point(-8, 18, 32));
}

TEST_CASE("multiplying a vector by a scaling matrix") {
    Tuple4 a = Vector(-4, 6, 8);
    Mat4 b = Scaling(2, 3, 4);

    CHECK(b * a == Vector(-8, 18, 32));
}

TEST_CASE("multiplying a vector by the inverse of a scaling matrix") {
    Tuple4 a = Vector(-4, 6, 8);
    Mat4 b = Scaling(2, 3, 4).invert();

    CHECK(b * a == Vector(-2, 2, 2));
}

TEST_CASE("reflection is scaling by a negative value") {
    Tuple4 a = Point(2, 3, 4);
    Mat4 b = Scaling(-1, 1, 1);

    CHECK(b * a == Point(-2, 3, 4));
}