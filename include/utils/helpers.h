#pragma once

#include "utils/macros.h"

#include "maths/matrix.h"


Mat4 ViewTransform(Tuple4 from, Tuple4 to, Tuple4 up); // TODO: reorganise this into macros.h? / move it elsewhere?