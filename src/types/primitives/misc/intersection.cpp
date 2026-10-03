#include "types/primitives/misc/intersection.h"

#include "maths/constants.h"
#include "utils/macros.h"

#include <iterator>
#include <cmath>


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

const Intersection IntersectionArray::findHit() const { // intersection with lowest nonnegative value
    int v = 0;

    for (int i=0; i < intersections.size(); i++) {
        if ((intersections[i].t > 0) && !assertEqual(intersections[v].t, intersections[i].t)) {
            if (intersections[v].t < 0) {
                v = i;
            } else {
                if (intersections[i].t < intersections[v].t) {
                    v = i;
                }
            }
        }
    }

    if ((intersections[v].t > 0) && notZero(intersections[v].t)) {
        return intersections[v];
    } else {
        return Intersection(); // null intersection (no hit)
    }
}