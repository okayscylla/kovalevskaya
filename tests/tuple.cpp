#include <doctest/doctest.h>

#include "utils/macros.h"
#include "maths/constants.h"
#include "maths/tuple.h"

#include <cmath>
#include <typeinfo>


TEST_CASE("tuple4 with w=1.0 is a point") {
    Tuple4 a = Tuple4(4.3, -4.2, 3.1, 1.0);

    CHECK(assertEqual(a.x, 4.3));
    CHECK(assertEqual(a.y, -4.2));
    CHECK(assertEqual(a.z, 3.1));
    CHECK(assertEqual(a.w, 1.0));

    CHECK(a.isPoint());
}

TEST_CASE("tuple4 with w=0.0 is a vector") {
    Tuple4 a = Tuple4(4.3, -4.2, 3.1, 0.0);

    CHECK(assertEqual(a.x, 4.3));
    CHECK(assertEqual(a.y, -4.2));
    CHECK(assertEqual(a.z, 3.1));
    CHECK(assertEqual(a.w, 0.0));

    CHECK(a.isVector());
}

TEST_CASE("point is a tuple4 with w=1.0") {
    Tuple4 a = Point(4, -4, 3);

    CHECK(assertEqual(a.x, 4));
    CHECK(assertEqual(a.y, -4));
    CHECK(assertEqual(a.z, 3));
    CHECK(assertEqual(a.w, 1.0));

    CHECK(typeid(a) == typeid(Tuple4));
}

TEST_CASE("vector is a tuple4 with w=0.0") {
    Tuple4 a = Vector(4, -4, 3);

    CHECK(assertEqual(a.x, 4));
    CHECK(assertEqual(a.y, -4));
    CHECK(assertEqual(a.z, 3));
    CHECK(assertEqual(a.w, 0.0));
    
    CHECK(typeid(a) == typeid(Tuple4));
}

TEST_CASE("adding two tuple4s") {
    Tuple4 a = Tuple4(3, -2, 5, 1);
    Tuple4 b = Tuple4(-2, 3, 1, 0);

    CHECK((a + b == Tuple4(1, 1, 6, 1)));
}

TEST_CASE("subtracting two tuple4s") {
    Tuple4 a = Tuple4(3, -2, 5, 1);
    Tuple4 b = Tuple4(-2, 3, 1, 0);

    CHECK((a - b == Tuple4(5, -5, 4, 1)));
}

TEST_CASE("subtracting a vector from a point") {
    Tuple4 a = Point(3, -2, 5);
    Tuple4 b = Vector(-2, 3, 1);

    CHECK((a - b == Tuple4(5, -5, 4, 1)));
    CHECK((a - b).isPoint());
}

TEST_CASE("subtracting two vectors") {
    Tuple4 a = Vector(3, -2, 5);
    Tuple4 b = Vector(-2, 3, 1);

    CHECK((a - b) == Tuple4(5, -5, 4, 0));
    CHECK((a - b).isVector());
}

TEST_CASE("negating a tuple4") {
    Tuple4 a = Tuple4(1, -2, 3, -4);

    CHECK((a.negate()) == Tuple4(-1, 2, -3, 4));
}

TEST_CASE("subtracting a vector from zero vector") {
    Tuple4 a = Tuple4(0, 0, 0, 0);
    Tuple4 b = Tuple4(1, -2, 3, -4);

    CHECK((a - b) == (b.negate()));
}

TEST_CASE("multiplying tuple4 by a scalar") {
    Tuple4 a = Tuple4(1, -2, 3, -4);

    CHECK((a * 2) == Tuple4(2, -4, 6, -8));
}

TEST_CASE("multiplying tuple4 by a fraction") {
    Tuple4 a = Tuple4(1, -2, 3, -4);

    CHECK((a * 0.5) == Tuple4(0.5, -1, 1.5, -2));
}

TEST_CASE("computing the magnitude of vector(1, 0, 0)") {
    Tuple4 a = Vector(1, 0, 0);

    CHECK(assertEqual(a.magnitude(), 1));
}

TEST_CASE("computing the magnitude of vector(-1, 2, 3)") {
    Tuple4 a = Vector(-1, 2, 3);

    CHECK(assertEqual(a.magnitude(), std::sqrtf(14)));
}

TEST_CASE("calculating unit vector of tuple4") {
    Tuple4 a = Vector(4, 0, 0);
    Tuple4 b = a.unitVector();

    CHECK((b == Vector(1, 0, 0)));
}

TEST_CASE("normalising a vector") {
    Tuple4 a = Vector(1, 2, 3);

    CHECK(a.normalise() == a);
    CHECK(assertEqual(a.x, 1/sqrtf(14)));
    CHECK(assertEqual(a.y, 2/std::sqrtf(14)));
    CHECK(assertEqual(a.z, 3/std::sqrtf(14)));
    CHECK(assertEqual(a.w, 0.0));
}

TEST_CASE("magnitude of normalised vector is 1") {
    Tuple4 a = Vector(7, -3, 2.5).normalise();

    CHECK(assertEqual(a.magnitude(), 1));
}

TEST_CASE("dot product of two vectors") {
    Tuple4 a = Vector(1, 2, 3);
    Tuple4 b = Vector(2, 3, 4);

    CHECK(assertEqual(a.dot(b), 20));
}

TEST_CASE("cross product of two vectors") {
    Tuple4 a = Vector(1, 2, 3);
    Tuple4 b = Vector(2, 3, 4);

    CHECK(a.cross(b) == Vector(-1, 2, -1));
    CHECK(b.cross(a) == a.cross(b).negate());
}

TEST_CASE("adding two tuple3s") {
    Tuple3 a = Tuple3(3, -2, 5);
    Tuple3 b = Tuple3(-2, 3, 1);

    CHECK((a + b == Tuple3(1, 1, 6)));
}

TEST_CASE("subtracting two tuple3s") {
    Tuple3 a = Tuple3(3, -2, 5);
    Tuple3 b = Tuple3(-2, 3, 1);

    CHECK((a - b == Tuple3(5, -5, 4)));
}

TEST_CASE("negating a tuple3") {
    Tuple3 a = Tuple3(1, -2, 3);

    CHECK((a.negate()) == Tuple3(-1, 2, -3));
}

TEST_CASE("multiplying tuple3 by a scalar") {
    Tuple3 a = Tuple3(1, -2, 3);

    CHECK((a * 2) == Tuple3(2, -4, 6));
}

TEST_CASE("multiplying tuple3 by a fraction") {
    Tuple3 a = Tuple3(1, -2, 3);

    CHECK((a * 0.5) == Tuple3(0.5, -1, 1.5));
}

TEST_CASE("computing the magnitude a tuple3") {
    Tuple3 a = Tuple3(-1, 2, 3);

    CHECK(assertEqual(a.magnitude(), std::sqrtf(14)));
}

TEST_CASE("calculating unit vector of tuple3") {
    Tuple3 a = Tuple3(4, 0, 0);
    Tuple3 b = a.unitVector();

    CHECK((b == Tuple3(1, 0, 0)));
}

TEST_CASE("normalising a tuple3") {
    Tuple3 a = Tuple3(1, 2, 3);

    CHECK(a.normalise() == a);
    CHECK(assertEqual(a.x, 1/sqrtf(14)));
    CHECK(assertEqual(a.y, 2/std::sqrtf(14)));
    CHECK(assertEqual(a.z, 3/std::sqrtf(14)));
}

TEST_CASE("magnitude of normalised tuple3 is 1") {
    Tuple3 a = Tuple3(7, -3, 2.5).normalise();

    CHECK(assertEqual(a.magnitude(), 1));
}

TEST_CASE("dot product of two tuple3s") {
    Tuple3 a = Tuple3(1, 2, 3);
    Tuple3 b = Tuple3(2, 3, 4);

    CHECK(assertEqual(a.dot(b), 20));
}

TEST_CASE("cross product of two tuple3s") {
    Tuple3 a = Tuple3(1, 2, 3);
    Tuple3 b = Tuple3(2, 3, 4);

    CHECK(a.cross(b) == Tuple3(-1, 2, -1));
    CHECK(b.cross(a) == a.cross(b).negate());
}