#pragma once

#include "types/primitives/primitive.h"
#include "types/scene/intersection.h"
#include "types/scene/light.h"

#include <vector>


struct World { // 67 hehe :3
    public:
    IntersectionArray intersect(Ray r) const;
    
    World& addObject(Primitive* object); // TODO: removable objects and lights
    World& addLight(PointLight* light); // TODO: lights need an id system too, maybe merge objects and lights into one metatype?

    bool isEmpty() const;
    Primitive* atID(int id);

    World(std::vector<Primitive*> _objects, std::vector<PointLight*> _lights) : objects(_objects), lights(_lights), next_free_id(_objects.back()->id + 1) {}
    World() : objects({}), lights({}), next_free_id(0) {}

    private:
    std::vector<Primitive*> objects;
    std::vector<PointLight*> lights; // TODO: use Light instead of PointLight (im too lazy to refactor rn)

    int next_free_id; // TODO: implement a better method than april (those who know :3)
};