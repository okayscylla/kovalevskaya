#pragma once

#include "types/basic/colour.h"
#include "types/scene/material.h"
#include "types/scene/light.h"
#include "types/scene/world.h"
#include "maths/tuple.h"

#include "utils/macros.h"


Colour calculateLighting(Material material, Tuple4 point, PointLight light, Tuple4 eye_vector, Tuple4 normal_vector); // TODO: make this work with stuff other than point lights

Colour shadeHit(World* a, ComputedIntersectionData v);

Colour colourAt(World* a, Ray r, Colour sky_colour = Black);