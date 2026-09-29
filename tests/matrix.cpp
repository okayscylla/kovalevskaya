#include "misc/base.h"

#include "maths/matrix.h"


TEST_CASE("creating a mat2") {
    Mat2 a = Mat2({
        1,2,
        3,4
    });
    
    CHECK(assertEqual(a[0][0], 1));
    CHECK(assertEqual(a[0][1], 2));
    CHECK(assertEqual(a[1][0], 3));
    CHECK(assertEqual(a[1][1], 4));

    CHECK(typeid(a) == typeid(Mat2));
}

TEST_CASE("comparing two equal mat2s") {
    Mat2 a = Mat2({
        1,2,
        3,4
    });
    Mat2 b = Mat2({
        1,2,
        3,4
    });

    CHECK(a == b);
}

TEST_CASE("comparing two inequal mat2s") {
    Mat2 a = Mat2({
        1,2,
        3,4
    });
    Mat2 b = Mat2({
        1,2,
        3,5
    });

    CHECK(a != b);
}

TEST_CASE("creating a mat3") {
    Mat3 a = Mat3({
        1,2,3,
        4,5,6,
        7,8,9
    });
    
    CHECK(assertEqual(a[0][0], 1));
    CHECK(assertEqual(a[0][2], 3));
    CHECK(assertEqual(a[1][1], 5));
    CHECK(assertEqual(a[2][2], 9));

    CHECK(typeid(a) == typeid(Mat3));
}

TEST_CASE("comparing two equal mat3s") {
    Mat3 a = Mat3({
        1,2,3,
        4,5,6,
        7,8,9
    });
    Mat3 b = Mat3({
        1,2,3,
        4,5,6,
        7,8,9
    });

    CHECK(a == b);
}
TEST_CASE("comparing two inequal mat3s") {
    Mat3 a = Mat3({
        1,2,3,
        4,5,6,
        7,8,9
    });
    Mat3 b = Mat3({
        1,2,3,
        4,5,6,
        7,8,10
    });

    CHECK(a != b);
}

TEST_CASE("creating a mat4") {
    Mat4 a = Mat4({
        1,2,3,4,
        5,6,7,8,
        9,10,11,12,
        13,14,15,16
    });
    
    CHECK(assertEqual(a[0][0], 1));
    CHECK(assertEqual(a[1][1], 6));
    CHECK(assertEqual(a[2][3], 12));
    CHECK(assertEqual(a[3][2], 15));

    CHECK(typeid(a) == typeid(Mat4));
}

TEST_CASE("comparing two equal mat4s") {
    Mat4 a = Mat4({
        1,2,3,4,
        5,6,7,8,
        9,10,11,12,
        13,14,15,16
    });
    Mat4 b = Mat4({
        1,2,3,4,
        5,6,7,8,
        9,10,11,12,
        13,14,15,16
    });

    CHECK(a == b);
}

TEST_CASE("comparing two inequal mat4s") {
    Mat4 a = Mat4({
        1,2,3,4,
        5,6,7,8,
        9,10,11,12,
        13,14,15,16
    });
    Mat4 b = Mat4({
        1,2,3,4,
        5,6,7,8,
        9,10,11,12,
        13,14,15,17
    });

    CHECK(a != b);
}

TEST_CASE("multiplying two mat4s") { // TODO: make test for Mat3
    Mat4 a = Mat4({
        1,2,3,4,
        5,6,7,8,
        9,8,7,6,
        5,4,3,2
    });
    Mat4 b = Mat4({
        -2,1,2,3,
        3,2,1,-1,
        4,3,6,5,
        1,2,7,8
    });

    CHECK(a * b == Mat4({
        20,22,50,48,
        44,54,114,108,
        40,58,110,102,
        16,26,46,42
    }));
}

TEST_CASE("multiplying a mat4 by a tuple4") { // TODO: make test for Mat3
    Mat4 a = Mat4({
        1,2,3,4,
        2,4,4,2,
        8,6,4,1,
        0,0,0,1
    });
    Tuple4 b = Tuple4(1, 2, 3, 1);

    CHECK(a * b == Tuple4(18, 24, 33, 1));
}