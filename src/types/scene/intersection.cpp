#include "types/scene/intersection.h"

#include "types/primitives/primitive.h"

#include "maths/constants.h"
#include "utils/macros.h"

#include <algorithm>
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
    if (size() > 0) {
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
    } else {
        return Intersection();
    }
}

IntersectionArray& IntersectionArray::sortAscending() {
    std::sort(
        intersections.begin(),
        intersections.end(),
        [](Intersection a, Intersection b) { // lambda functions my beloved
            return a.t < b.t;
        }
    );

    return *this;
}

ComputedIntersectionData prepareComputations(Intersection i, Ray r) { // FIXME: why is this in types
    Tuple4 _normalv = i.object->normalAt(r.at(i.t));
    
    if (_normalv.dot(r.direction.negate()) < 0) {
        return {
            .t = i.t,
            .object = i.object,
            .point = r.at(i.t),
            .eyev = r.direction.negate(),
            .normalv = _normalv.negate(),
            .inside = true
        };
    } else {
        return {
            .t = i.t,
            .object = i.object,
            .point = r.at(i.t),
            .eyev = r.direction.negate(),
            .normalv = _normalv,
            .inside = false
        };
    }
}