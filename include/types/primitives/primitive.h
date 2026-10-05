#pragma once

#include "maths/matrix.h"
#include "maths/tuple.h"
#include "types/primitives/misc/ray.h"
#include "types/primitives/misc/intersection.h"


class Primitive {
    public:
    const int id;

    virtual IntersectionArray intersect(Ray r) const;
    virtual Tuple4 normalAt(const Tuple4 p, bool world_space = true) const;
    
    Primitive& transform(const Mat4 operand); // TODO: implement Primitive::transformed / decide what that should do

    Primitive(int _id) : id(_id) {} // FIXME: implement some sort of scene manager class to assign these automatically

    virtual ~Primitive() {}

    protected:
    Mat4 transformation = Mat4(); // yay identity matrix :3
};