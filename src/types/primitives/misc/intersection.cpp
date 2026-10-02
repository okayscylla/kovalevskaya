#include "types/primitives/misc/intersection.h"


int IntersectionArray::size() const {
    return intersections.size();
}

IntersectionArray IntersectionArray::append(const Intersection intersection) {
    intersections.push_back(intersection);

    return *this;
}

const Intersection IntersectionArray::findHit() const {
    return intersections[0];
}

const Intersection IntersectionArray::operator[](int i) const {
    return intersections[i];
}