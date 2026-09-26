#include <doctest/doctest.h>

#include "utils/macros.h"
#include "types/colour.h"
#include "maths/constants.h"

#include <cmath>


TEST_CASE("colors have red, green, and blue components") {
    Colour a = Colour(-0.5, 0.4, 1.7);

    CHECK(assertEqual(a.red, -0.5));
    CHECK(assertEqual(a.green, 0.4));
    CHECK(assertEqual(a.blue, 1.7));
}

TEST_CASE("adding colors") {
    Colour a = Colour(0.9, 0.6, 0.75);
    Colour b = Colour(0.7, 0.1, 0.25);

    CHECK(((a + b) == Colour(1.6, 0.7, 1.0)));
}

TEST_CASE("subtracting colors") {
    Colour a = Colour(0.9, 0.6, 0.75);
    Colour b = Colour(0.7, 0.1, 0.25);

    CHECK(((a - b) == Colour(0.2, 0.5, 0.5)));
}

TEST_CASE("multiplying color by scalar") {
    Colour a = Colour(0.2, 0.3, 0.4);

    CHECK(((a * 2) == Colour(0.4, 0.6, 0.8)));
}

TEST_CASE("multiplying colors") {
    Colour a = Colour(1.0, 0.2, 0.4);
    Colour b = Colour(0.9, 1.0, 0.1);

    CHECK(((a * b) == Colour(0.9, 0.2, 0.04)));
}