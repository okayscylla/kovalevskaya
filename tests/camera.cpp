#include "misc/base.h"

#include "types/scene/camera.h"


TEST_CASE("constructing a camera") {
    Camera a = Camera(160, 120, PI / 2);

    CHECK(a.width == 160);
    CHECK(a.height == 120);
    CHECK(a.fov == (PI / 2));
    CHECK(a.transformation == Mat4());
}

TEST_CASE("calculating pixel size (horizonal canvas)") {
    Camera a = Camera(200, 125, PI / 2);

    CHECK(assertEqual(a.pixel_size, 0.01));
}

TEST_CASE("calculating pixel size (vertical canvas)") {
    Camera a = Camera(125, 200, PI / 2);

    CHECK(assertEqual(a.pixel_size, 0.01));
}

TEST_CASE("ray through the centre of canvas") {
    Camera a = Camera(201, 101, PI / 2);

    Ray r = a.pixelToRay(100, 50);

    CHECK(r.origin == Point(0,0,0));
    CHECK(r.direction == Vector(0,0,-1));
}

TEST_CASE("ray through the corner of canvas") {
    Camera a = Camera(201, 101, PI / 2);

    Ray r = a.pixelToRay(0, 0);

    CHECK(r.origin == Point(0,0,0));
    CHECK(r.direction == Vector(0.66519,0.33259,-0.66851));
}

TEST_CASE("ray through centre of canvas (transformed)") {
    Camera a = Camera(201, 101, PI / 2);
    a.transform(RotateY(PI / 4) * Translate(0,-2,5));

    Ray r = a.pixelToRay(100, 50);

    CHECK(r.origin == Point(0,2,-5));
    CHECK(r.direction == Vector(std::sqrtf(2) / 2,0,-(std::sqrtf(2)) / 2));
}