#pragma once

#include "types/basic/colour.h"
#include "types/scene/material.h"
#include "types/scene/light.h"
#include "maths/tuple.h"


namespace Phong { // TODO: reorganise this and move it out of the raytracer implementation
    Colour calculateLighting(Material material, Tuple4 point, PointLight light, Tuple4 eye_vector, Tuple4 normal_vector); // TODO: make this work with stuff other than point lights
}