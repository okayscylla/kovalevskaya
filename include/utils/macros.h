#pragma once

#include "maths/constants.h"

#include <cmath>

#define assertEqual(i, j)           (std::fabs((i) - (j)) < EPSILON)
#define notZero(i)                  (std::fabs(i) < EPSILON)
