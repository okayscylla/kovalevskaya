#pragma once

#include "maths/matrix.h"
#include "types/scene/ray.h"


struct Camera {
    public:
    int width, height; // FIXME: this should be private but then tests wouldn't pass
    float fov; // FIXME: (see above)
    float pixel_size; // FIXME: (see above)
    Mat4 transformation; // FIXME: (see above)

    Camera& transform(Mat4 _transformation); // helper that automatically calls updatePixelSize
    Camera& setFOV(int fov); // helper that automatically calls updatePixelSize
    Camera& setSize(int w, int h); // helper that automatically calls updatePixelSize

    void updatePixelSize(); // FIXME: this should be private but then tests wouldn't pass
    Ray pixelToRay(int x, int y); // FIXME: (see above)

    Camera(int w, int h, float _fov) : width(w), height(h), fov(_fov), transformation(Mat4()) { updatePixelSize(); }

    private:
    float half_width, half_height; // TODO: maybe get rid of these?
};