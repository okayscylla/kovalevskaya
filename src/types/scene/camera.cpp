#include "types/scene/camera.h"

#include "utils/macros.h"

#include <cmath>


Camera& Camera::transform(Mat4 _transformation) {
    transformation *= _transformation;

    updatePixelSize();

    return *this;
}

void Camera::updatePixelSize() { // TODO: maybe this should result a reference to self instead of void?
    float half_view = std::tanf((float)fov / 2);
    float aspect_ratio = (float)camera.width / camera.height; // camera.height is implicitly cast to float

    if (aspect_ratio < 1) {
        half_width = half_view * aspect_ratio;
        half_height = half_view;
    } else {
        half_width = half_view;
        half_height = half_view / aspect_ratio;
    }

    pixel_size = (half_width * 2) / width; // why does this work

    Tuple4 pixel = transformation.inverse() * Point(world_x, world_y, -1); // why does this work
    Tuple4 origin = transformation.inverse() * Point(0,0,0);

    Tuple4 direction = (pixel - origin).normalise(); // scawy

    return Ray(origin, direction);
}

Ray Camera::pixelToRay(int x, int y) {
    float x_offset = ((float)x + 0.5) * pixel_size;
    float y_offset = ((float)y + 0.5) * pixel_size;

    float world_x = half_width - x_offset;
    float world_y = half_height - y_offset;
}