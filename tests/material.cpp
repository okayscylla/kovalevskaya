#include "misc/base.h"

#include "types/basic/colour.h"
#include "types/scene/material.h"
#include "types/scene/light.h"
#include "maths/tuple.h"
#include "render/raytracer/lighting.h"


TEST_CASE("material smth smth im silly :3") {
    Material s = Material();

    CHECK(s.colour == Colour(1,1,1));
    CHECK(s.ambient == 0.1f);
    CHECK(s.diffuse == 0.9f);
    CHECK(s.specular == 0.9f);
    CHECK(s.shininess == 200.f);
}

TEST_CASE("phong lighting with the eye between light and surface") {
    Material material = Material();
    Tuple4 position = Point(0, 0, 0);
    Tuple4 eye_vector = Vector(0, 0, -1);
    Tuple4 normal_vector = Vector(0, 0, -1);
    PointLight light = PointLight(Point(0, 0, -10), Colour(1, 1, 1));

    Colour lighting = calculateLighting(material, position, light, eye_vector, normal_vector, false);

    CHECK(lighting == Colour(1.9, 1.9, 1.9));
}

TEST_CASE("phong lighting with the eye between light and surface (eye offset pi / 4 radians)") {
    Material material = Material();
    Tuple4 position = Point(0, 0, 0);
    Tuple4 eye_vector = Vector(0, std::sqrtf(2) / 2, -(std::sqrtf(2) / 2));
    Tuple4 normal_vector = Vector(0, 0, -1);
    PointLight light = PointLight(Point(0, 0, -10), Colour(1, 1, 1));

    Colour lighting = calculateLighting(material, position, light, eye_vector, normal_vector, false);

    CHECK(lighting == Colour(1.f, 1.f, 1.f));
}

TEST_CASE("phong lighting with the eye oppsite surface (light offset pi / 4 radians)") {
    Material material = Material();
    Tuple4 position = Point(0, 0, 0);
    Tuple4 eye_vector = Vector(0, 0, -1);
    Tuple4 normal_vector = Vector(0, 0, -1);
    PointLight light = PointLight(Point(0, 10, -10), Colour(1, 1, 1));

    Colour lighting = calculateLighting(material, position, light, eye_vector, normal_vector, false);

    CHECK(lighting == Colour(0.7364, 0.7364, 0.7364));
}

TEST_CASE("lighting with eye in the path of reflection vector") {
    Material material = Material();
    Tuple4 position = Point(0, 0, 0);
    Tuple4 eye_vector = Vector(0, -(std::sqrtf(2) / 2), -(std::sqrtf(2) / 2));
    Tuple4 normal_vector = Vector(0, 0, -1);
    PointLight light = PointLight(Point(0, 10, -10), Colour(1, 1, 1));

    Colour lighting = calculateLighting(material, position, light, eye_vector, normal_vector, false);

    CHECK(lighting == Colour(1.63639, 1.63639, 1.63639));
}

TEST_CASE("phong lighting with light behind surface") {
    Material material = Material();
    Tuple4 position = Point(0, 0, 0);
    Tuple4 eye_vector = Vector(0, 0, -1);
    Tuple4 normal_vector = Vector(0, 0, -1);
    PointLight light = PointLight(Point(0, 0, 10), Colour(1, 1, 1));

    Colour lighting = calculateLighting(material, position, light, eye_vector, normal_vector, false);

    CHECK(lighting == Colour(0.1, 0.1, 0.1));
}