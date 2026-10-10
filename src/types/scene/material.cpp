#include "types/scene/material.h"

#include "maths/constants.h"
#include "utils/macros.h"

#include <cmath>


bool Material::operator==(const Material operand) const {
    return (
        assertEqual(ambient, operand.ambient) &&
        assertEqual(diffuse, operand.diffuse) &&
        assertEqual(specular, operand.specular) &&
        assertEqual(shininess, operand.shininess)
    );
}