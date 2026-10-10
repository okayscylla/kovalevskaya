#pragma once

#include "maths/constants.h"

#include <vector>


class Primitive; // forward declartion scawy

struct Intersection { // TODO: add ==, !=, etcetera operators
    public:
    const float t;
    const Primitive* object;
    const bool null; // TODO: find a better way of doing this :3

    Intersection(float _t, const Primitive* _object) : t(_t), object(_object), null(false) {}
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

    IntersectionArray(std::vector<Intersection> _intersections) : intersections(_intersections) {}
    IntersectionArray() : intersections({}) {}

    private:
    std::vector<Intersection> intersections;
};