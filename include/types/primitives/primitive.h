#pragma once

#include "maths/matrix.h"
#include "maths/tuple.h"
#include "types/scene/ray.h"
#include "types/scene/intersection.h"
#include "types/scene/material.h"


class Primitive {
    public:
    int id; // TODO: reorganise so this is const
    Material material;

    virtual IntersectionArray intersect(Ray r) const;
    virtual Tuple4 normalAt(const Tuple4 p, bool world_space = true) const;
    
    Primitive& transform(const Mat4 operand); // TODO: implement Primitive::transformed / decide what that should do
    Primitive& init(int _id);

    Primitive(int _id, Material _material) : id(_id), material(_material) {} // FIXME: implement some sort of scene manager class to assign these automatically
    Primitive(int _id) : id(_id), material(Material()) {} // FIXME: implement some sort of scene manager class to assign these automatically
    Primitive(Material _material) : material(_material) {} // world needs to call init on this

    virtual ~Primitive() {}

    protected:
    Mat4 transformation = Mat4(); // yay identity matrix :3
};