#pragma once

#include "render/renderer.h"


class ColouredScreen : public Renderer {
    public:
    void draw();
    void writePixel(int x, int y);
};