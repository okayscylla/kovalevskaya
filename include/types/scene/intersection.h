#pragma once

#include "maths/constants.h"
#include "maths/tuple.h"
#include "types/scene/ray.h"

#include <vector>


class Primitive; // forward declartion scawy

struct Intersection { // TODO: add ==, !=, etcetera operators
    public:
    float t;
    Primitive* object;
    bool null; // TODO: find a better way of doing this :3

    Intersection(float _t, Primitive* _object) : t(_t), object(_object), null(false) {}
    Intersection() : t(-INFINITY), object(nullptr), null(true) {}
};

struct IntersectionArray { // TODO: add ==, !=, etcetera operators
    public:
    IntersectionArray operator+(const IntersectionArray operand) const;
    IntersectionArray& operator+=(const IntersectionArray operand);

    const Intersection operator[](const int i) const;

    int size() const;
    IntersectionArray append(const Intersection intersection);
    const Intersection findHit() const;

    IntersectionArray& sortAscending();

    IntersectionArray(std::vector<Intersection> _intersections) : intersections(_intersections) {}
    IntersectionArray() : intersections({}) {}

    private:
    std::vector<Intersection> intersections;
};

struct ComputedIntersectionData {
    public:
    const float t; // :huh:
    const Primitive* object; // :buh:
    const Tuple4 point; // :wuh:
    const Tuple4 eyev; // :luh:
    const Tuple4 normalv; // :guh:
    const bool inside; // :cuh:
};

ComputedIntersectionData prepareComputations(Intersection i, Ray r); // TODO: maybe make this a member of ComputedIntersectionData?