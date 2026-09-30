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

TEST_CASE("determinant of a mat2") {
    Mat2 a = Mat2({
        1,5,
        -3,2
    });

    CHECK(a.determinant() == 17);
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

TEST_CASE("submatrix of a mat3") {
    Mat3 a = Mat3({
        1,5,0,
        -3,2,7,
        0,6,-3
    });
    Mat2 b = Mat2({
        -3,2,
        0,6
    });

    CHECK(a.submatrix(0, 2) == b);
}

TEST_CASE("determinant of a mat3") {
    Mat3 a = Mat3({
        1,2,6,
        -5,8,-4,
        2,6,4
    });

    CHECK(a.cofactor(0, 0) == 56);
    CHECK(a.cofactor(0, 1) == 12);
    CHECK(a.cofactor(0, 2) == -46);
    CHECK(a.determinant() == -196);
}

TEST_CASE("calculating a minor of a mat3") { // TODO: add tests for Mat4, Mat2
    Mat3 a = Mat3({
        3,5,0,
        2,-1,-7,
        6,-1,5
    });
    Mat2 b = a.submatrix(1, 0);

    CHECK(b.determinant() == 25);
    CHECK(a.minor(1, 0) == 25);
}

TEST_CASE("calculating a cofactor of a mat3") { // TODO: add tests for Mat4, Mat2
    Mat3 a = Mat3({
        3,5,0,
        2,-1,-7,
        6,-1,5
    });

    CHECK(a.minor(0, 0) == -12);
    CHECK(a.cofactor(0, 0) == -12);
    CHECK(a.minor(1, 0) == 25);
    CHECK(a.cofactor(1, 0) == -25);
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
    Mat4 c = Mat4({
        20,22,50,48,
        44,54,114,108,
        40,58,110,102,
        16,26,46,42
    });

    CHECK(a * b == c);
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

TEST_CASE("multiplying a mat4 by an identity matrix") { // TODO: make test for Mat3, Mat2
    Mat4 a = Mat4({
        1,2,3,4,
        2,4,4,2,
        8,6,4,1,
        0,0,0,1
    });
    Mat4 b;

    CHECK(a * b == a);
}

TEST_CASE("transposing a mat4") { // TODO: make test for Mat3, Mat2
    Mat4 a = Mat4({
        0,9,3,0,
        9,8,0,8,
        1,8,5,3,
        0,0,5,8
    });
    Mat4 b = Mat4({
        0,9,1,0,
        9,8,8,0,
        3,0,5,5,
        0,8,3,8
    });

    CHECK(a.transpose() == b);
}

TEST_CASE("submatrix of a mat4") {
    Mat4 a = Mat4({
        -6,1,1,6,
        -8,5,8,6,
        -1,0,8,2,
        -7,1,-1,1
    });
    Mat3 b = Mat3({
        -6,1,6,
        -8,8,6,
        -7,-1,1
    });

    CHECK(a.submatrix(2, 1) == b);
}

TEST_CASE("determinant of a mat4") {
    Mat4 a = Mat4({
        -2,-8,3,5,
        -3,1,7,3,
        1,2,-9,6,
        -6,7,7,-9
    });

    CHECK(a.cofactor(0, 0) == 690);
    CHECK(a.cofactor(0, 1) == 447);
    CHECK(a.cofactor(0, 2) == 210);
    CHECK(a.cofactor(0, 3) == 51);
    CHECK(a.determinant() == -4071);
}

TEST_CASE("testing a invertible matrix for invertibility") {
    Mat4 a = Mat4({
        6,4,4,4,
        5,5,7,6,
        4,-9,3,-7,
        9,1,7,-6
    });

    CHECK(a.determinant() == -2120);
    CHECK(a.invertible() == true);
}

TEST_CASE("testing a noninvertible matrix for invertibility") {
    Mat4 a = Mat4({
        -4,2,-2,-3,
        9,6,2,6,
        0,-5,1,-5,
        0,0,0,0
    });

    CHECK(a.determinant() == 0);
    CHECK(a.invertible() == false);
}

TEST_CASE("inverse of a mat4") { // TODO: implement more tests for matrix inversion
    Mat4 a = Mat4({
        -5,2,6,-8,
        1,-5,1,8,
        7,7,-6,-7,
        1,-3,7,4
    });
    Mat4 b = a.inverse();

    CHECK(a.determinant() == 532);
    CHECK(a.cofactor(2, 3) == -160);
    CHECK(assertEqual(b[3][2], (-160.f/532.f)));
    CHECK(a.cofactor(3, 2) == 105);
    CHECK(assertEqual(b[2][3], (105.f/532.f)));
}

TEST_CASE("inverse matrices reverse operations") {
    Mat4 a = Mat4({
        3,-9,7,3,
        3,-8,2,-9,
        -4,4,4,1,
        -6,5,-1,1
    });
    Mat4 b = Mat4({
        8,2,2,2,
        3,-1,7,0,
        7,0,5,4,
        6,-2,0,5
    });
    Mat4 c = a * b;

    Mat4 d = c * b.inverse();

    CHECK(d == a);
}