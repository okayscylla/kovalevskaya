#pragma once


struct Material {
    public:
    const float ambient, diffuse, specular, shininess;

    Material(float am, float di, float sp, float sh) : ambient(am), diffuse(di), specular(sp), shininess(sh) {}
    Material() : ambient(0.1f), diffuse(0.9f), specular(0.9f), shininess(200.f) {} // default material :3
};