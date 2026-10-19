#include "utils/helpers.h"


Mat4 ViewTransform(Tuple4 from, Tuple4 to, Tuple4 up) {
    Tuple4 forward = (to - from).normalise();
    Tuple4 up_normalised = up.normalise(); // trust
    Tuple4 left = forward.cross(up_normalised);
    Tuple4 up_real = left.cross(forward);

    Mat4 orientation = Mat4(
        left.x,left.y,left.z,0,
        up_real.x,up_real.y,up_real.z,0,
        -forward.x,-forward.y,-forward.z,0,
        0,0,0,1
    );

    return orientation * Translate(-from.x,-from.y,-from.z);
}