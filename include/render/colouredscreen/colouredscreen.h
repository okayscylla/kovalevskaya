#pragma once

#include "render/renderer.h"

#include <cstdint>


class ColouredScreen : public Renderer {
    public:
    const int id = 1; // FIXME: idk inheritance shit

    void init(SDL_GPUDevice* gpu, SDL_Window* window, int w, int h);
    void draw();
    void cleanup();

    private:
    void writePixel(int x, int y, uint32_t value);

    SDL_GPUTransferBuffer* _g_tbhdl;
    SDL_GPUTexture* _g_imthdl;
    void* _g_tbloc;
};