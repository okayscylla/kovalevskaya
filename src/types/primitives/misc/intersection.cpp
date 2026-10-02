#include "types/primitives/misc/intersection.h"

#include <iterator>


IntersectionArray IntersectionArray::operator+(const IntersectionArray operand) const {
    IntersectionArray v = IntersectionArray(intersections);

    std::copy(
        operand.intersections.begin(),
        operand.intersections.end(),
        std::back_inserter(v.intersections)
    );

    return v;
}

IntersectionArray& IntersectionArray::operator+=(const IntersectionArray operand) {    
    std::copy(
        operand.intersections.begin(),
        operand.intersections.end(),
        std::back_inserter(intersections)
    );

    return *this;
}

const Intersection IntersectionArray::operator[](const int i) const {
    return intersections[i];
}

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