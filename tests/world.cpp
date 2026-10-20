#include "misc/base.h"

#include "types/scene/world.h"

#include "types/primitives/sphere.h"

#include "render/raytracer/lighting.h"
#include "types/scene/light.h"


// TEST_CASE("empty world") { // FIXME: find a different way of testing this
//     World a = World();

//     CHECK(a.objects == {});
//     CHECK(a.lights == {});
// }

TEST_CASE("default world") { // FIXME: this is not a complete check of equality im only checking materials
    World a = DefaultWorld;

    CHECK(a.atID(0)->material == Material(Colour(0.8,1.0,0.6),0.1,0.7,0.2,200));
    CHECK(a.atID(1)->material == Material()); // does s1 have the default material or not?
}

// TEST_CASE("intersecting a world with a ray") { // FIXME: make doctest not have a heart attack
//     World a = DefaultWorld;

//     IntersectionArray x = a.intersect(Ray(Point(0,0,-5),Vector(0,0,1)));

//     CHECK(x.size() == 4);
//     CHECK(x[0].t = 4.f);
//     CHECK(x[1].t = 4.5);
//     CHECK(x[2].t = 5.5);
//     CHECK(x[3].t = 6.f);
// }

TEST_CASE("shading an intersection (outside)") {
    World a = DefaultWorld;
    ComputedIntersectionData v = prepareComputations(
        Intersection(4, a.atID(0)),
        Ray(Point(0,0,-5),Vector(0,0,1))
    );

    Colour c = a.shadeHit(v);

    CHECK(c == Colour(0.380661,0.475827,0.285496));
}

TEST_CASE("shading an intersection (inside)") {
    World a = World(
        {
            new Sphere(0,Material(Colour(0.8,1.0,0.6),0.1,0.7,0.2,200)),&
            (new Sphere(1))->transform(Scale(0.5,0.5,0.5))
        },
        {
            new PointLight(Point(0,0.25,0))
        }
    );
    ComputedIntersectionData v = prepareComputations(
        Intersection(0.5, a.atID(1)),
        Ray(Point(0,0,0),Vector(0,0,1))
    );

    CHECK(v.inside == true);

    Colour c = a.shadeHit(v);

    CHECK(c == Colour(0.904984,0.904984,0.904984));
}

TEST_CASE("the colour when a ray misses") {
    World a = DefaultWorld;
    Ray r = Ray(Point(0,0,-5),Vector(0,1,0));

    Colour c = a.colourAt(r);

    CHECK(c == Black);
}

TEST_CASE("the colour when a ray hits") {
    World a = DefaultWorld;
    Ray r = Ray(Point(0,0,-5),Vector(0,0,1));

    Colour c = a.colourAt(r);

    CHECK(c == Colour(0.380661,0.475827,0.285496));
}

TEST_CASE("the colour at at an intersection behind the ray") {
    World a = DefaultWorld;
    Material m = Material(White,1.0,0.9,0.9,200);
    a.atID(0)->material = m;
    a.atID(1)->material = m;
    Ray r = Ray(Point(0,0,0.75),Vector(0,0,-1));

    Colour c = a.colourAt(r);

    CHECK(c == a.atID(1)->material.colour);
}