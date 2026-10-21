#include "render/raytracer/lighting.h"

#include "maths/constants.h"
#include "utils/macros.h"
#include "types/scene/world.h"
#include "types/scene/camera.h"

#include <cmath>


Colour calculateLighting(Material material, Tuple4 point, PointLight light, Tuple4 eye_vector, Tuple4 normal_vector) {
    Colour effective_colour = material.colour * light.intensity;

    Colour ambient = effective_colour * material.ambient;
    Colour diffuse = Black; // no contribution
    Colour specular = Black; // no contribution

    Tuple4 light_vector = (light.position - point).normalise();

    float on_surface_side = light_vector.dot(normal_vector); // float representing how much the light is on the side of the surface

    if (isZero(on_surface_side)) { on_surface_side = 0.f; }

    if (on_surface_side < 0) {
        return ambient; // point is not in view of light source o7 :frown:
    } else {
        diffuse = effective_colour * material.diffuse * on_surface_side;

        Tuple4 reflect_vector = light_vector.negated().reflect(normal_vector);

        float reflects_towards_eye = reflect_vector.dot(eye_vector);

        if (isZero(reflects_towards_eye)) { reflects_towards_eye = 0.f; }

        if (reflects_towards_eye > 0) {
            float scale_factor = std::powf(reflects_towards_eye, material.shininess);

            specular = light.intensity * material.specular * scale_factor;
        }
    }

    return ambient + diffuse + specular;
}

Colour shadeHit(World* a, ComputedIntersectionData v) { // FIXME: don't hardcode lighting model
    // if (v.inside) { // FIXME: make this optimisation work
    //     Colour effective_colour = v.object->material.colour * lights[0]->intensity;
    //     return effective_colour * v.object->material.ambient;
    // } else {

    Point p_offset = v.point + (v.normalv * EPSILON); // offset point by a tiny bit to bprevent screen ance

    bool shadowed = isShadowed(&a, p_offset);

    return calculateLighting(
        v.object->material,
        p_offset, // FIXME: should p_offset be precomputed in prepareComputations?
        *a->lights[0], // FIXME: do this for every light in scene
        v.eyev,
        v.normalv
    );
    // }
}

Colour colourAt(World* a, Ray r, Colour c) {
    IntersectionArray xr = a->intersect(r);

    Intersection x = xr.findHit();

    if (x.null) {
        return c; // TODO: refactor this
    } else {
        ComputedIntersectionData v = prepareComputations(x, r);

        return shadeHit(a, v);
    }
}

bool isShadowed(World* a, Tuple4 p) {
    Tuple4 v = w->lights[0]->position - p; // spooky stories tell teachers abt little vro
    float dist = v.magnitude();

    v.normalise();

    Ray r = Ray(p, v);
    IntersectionArray xr = a->intersect(r);

    Intersection h = xr.findHit();

    if (!h.null && (h.t < distance)) {
        return true;
    }

    return false;
}