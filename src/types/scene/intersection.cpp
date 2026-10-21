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

const Intersection IntersectionArray::findHit() { // intersection with lowest nonnegative value
    sortAscending();

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
    popNullIntersections();

    std::sort(
        intersections.begin(),
        intersections.end(),
        [](const Intersection a, const Intersection b) { // lambda functions my beloved
            return a.t < b.t;
        }
    );

    return *this;
}

void IntersectionArray::popNullIntersections() { // TODO: optimise this / is it even necessary?
    intersections.erase(
        std::remove_if(
            intersections.begin(),
            intersections.end(),
            [](const Intersection a) {
                return a.null;
            }
        ),
        intersections.end()
    );
}

ComputedIntersectionData prepareComputations(Intersection i, Ray r) { // FIXME: why is this in types
    Tuple4 _normalv = i.object->normalAt(r.at(i.t));
    
    if (_normalv.dot(r.direction.negated()) < 0) {
        return {
            .t = i.t,
            .object = i.object,
            .point = r.at(i.t),
            .eyev = r.direction.negated(),
            .normalv = _normalv.negated(),
            .inside = true
        };
    } else {
        return {
            .t = i.t,
            .object = i.object,
            .point = r.at(i.t),
            .eyev = r.direction.negated(),
            .normalv = _normalv,
            .inside = false
        };
    }
}