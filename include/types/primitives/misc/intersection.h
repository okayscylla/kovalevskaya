#pragma once

#include <vector>


class Primitive; // forward declartion scawy

struct Intersection {
    public:
    const float t;
    const Primitive* object;

    Intersection(float _t, const Primitive* _object) : t(_t), object(_object) {}
};

struct IntersectionArray {
    public:
    const Intersection operator[](int i) const;

    int size() const;
    IntersectionArray append(const Intersection intersection);
    const Intersection findHit() const;

    IntersectionArray(std::vector<Intersection> _intersections) : intersections(_intersections) {}

    private:
    std::vector<Intersection> intersections;
};