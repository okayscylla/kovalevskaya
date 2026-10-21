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

    Colour c = shadeHit(&a, v);

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

    Colour c = shadeHit(&a, v);

    CHECK(c == Colour(0.904984,0.904984,0.904984));
}

TEST_CASE("the colour when a ray misses") {
    World a = DefaultWorld;
    Ray r = Ray(Point(0,0,-5),Vector(0,1,0));

    Colour c = colourAt(&a, r);

    CHECK(c == Black);
}

TEST_CASE("the colour when a ray hits") {
    World a = DefaultWorld;
    Ray r = Ray(Point(0,0,-5),Vector(0,0,1));

    Colour c = colourAt(&a, r);

    CHECK(c == Colour(0.380661,0.475827,0.285496));
}

TEST_CASE("the colour at at an intersection behind the ray") {
    World a = DefaultWorld;
    Material m = Material(White,1.0,0.9,0.9,200);
    a.atID(0)->material = m;
    a.atID(1)->material = m;
    Ray r = Ray(Point(0,0,0.75),Vector(0,0,-1));

    Colour c = colourAt(&a, r);

    CHECK(c == a.atID(1)->material.colour);
}

TEST_CASE("lighting with a surface in shadow") {
    Tuple4 eyev = Vector(0,0,-1);
    Tuple4 normalv = Vector(0,0,-1);
    PointLight light = PointLight(Point(0,0,-10),Colour(1,1,1));
    bool in_shadow = true;

    Colour result = calculateLighting(Material(),Point(0,0,0),light,eyev,normalv,in_shadow);

    CHECK(result == Colour(0.1,0.1,0.1));
}

TEST_CASE("the shadow when nothing when nothing is collinear with point and light") {
    World a = DefaultWorld;
    Tuple4 p = Point(0,10,0);

    CHECK(isShadowed(&a, p) == false);
}

TEST_CASE("the shadow when object is between the point and the light") {
    World a = DefaultWorld;
    Tuple4 p = Point(10,-10,10);

    CHECK(isShadowed(&a, p) == true);
}

TEST_CASE("the shadow when object is behind the point") {
    World a = DefaultWorld;
    Tuple4 p = Point(-2,2,-2);

    CHECK(isShadowed(&a, p) == false);
}

TEST_CASE("shading a hit that lies in shadow") {
    World a = World();
    a.addLight(new PointLight(Point(0,0,-10),Colour(1,1,1)));
    a.addObject(new Sphere(-1));
    a.addObject(new Sphere(-1));
    a.atID(1)->transform(Translate(0,0,10));

    Ray r = Ray(Point(0,0,5),Vector(0,0,1));
    Intersection x = Intersection(4, a.atID(1));

    ComputedIntersectionData v = prepareComputations(x, r);
    Colour c = shadeHit(&a, v);

    CHECK(c == Colour(0.1,0.1,0.1));
}