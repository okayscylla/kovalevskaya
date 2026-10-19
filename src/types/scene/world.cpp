#include "types/scene/world.h"

#include "render/raytracer/lighting.h" // TODO: the ray tracer implementation and lighting models


IntersectionArray World::intersect(Ray r) const {
    IntersectionArray arr;

    for (Primitive obj : objects) { // TODO: implement a BVH
        arr += obj.intersect(r);
    }

    arr.sortAscending();

    return arr;
}

World& World::addObject(Primitive object) {
    object.init(next_free_id);
    objects.push_back(object);

    next_free_id++;
}

World& World::addLight(Light light) { // yeah
    lights.push_back(light);
}

bool World::isEmpty() const {
    return ((objects.size() == 0) && (lights.size() == 0));
}

Primitive World::atId(int id) const {
    return object[id]; // FIXME: this is just a hack and an awful idea lol
}

Colour World::shadeHit(ComputedIntersectionData v) const { // FIXME: don't hardcode lighting model
    return Phong::calculateLighting(
        v.object->material,
        lights[0], // FIXME: do this for every light in scene
        v.point,
        v.eyev,
        v.normalv
    );
}

Colour World::colourAt(Ray r) const {
    IntersectionArray xr = intersect(r);

    Intersection x = x.findHit();

    if (x.null) {
        return Black;
    } else {
        ComputedIntersectionData v = prepareComputations(x, r);

        return shadeHit(v);
    }
}