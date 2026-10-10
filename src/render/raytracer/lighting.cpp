#include "render/raytracer/lighting.h"

#include "maths/constants.h"
#include "utils/macros.h"

#include <cmath>


Colour Phong::calculateLighting(Material material, Tuple4 point, PointLight light, Tuple4 eye_vector, Tuple4 normal_vector) {
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

        Tuple4 reflect_vector = light_vector.negate().reflect(normal_vector);

        float reflects_towards_eye = reflect_vector.dot(eye_vector);

        if (isZero(reflects_towards_eye)) { reflects_towards_eye = 0.f; }

        if (reflects_towards_eye > 0) {
            float scale_factor = std::powf(reflects_towards_eye, material.shininess);

            specular = light.intensity * material.specular * scale_factor;
        }
    }

    return ambient + diffuse + specular;
}