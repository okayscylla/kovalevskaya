#pragma once

#include "types/primitives/misc/ray.h"
#include "types/primitives/misc/intersection.h"


class Primitive {
    public:
    const int id;

    virtual IntersectionArray intersect(Ray r) const;

    Primitive(int _id) : id(_id) {} // FIXME: implement some sort of scene manager class to assign these automatically

    virtual ~Primitive() {}
};