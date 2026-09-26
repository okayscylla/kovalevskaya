#pragma once

#include "render/renderer.h"

#include <cstdint>


class ColouredScreen : public Renderer {
    public:
    void init(SDL_GPUDevice* gpu, SDL_Window* window, int w, int h);
    void draw();
    void cleanup();

    private:
    void writePixel(int x, int y, uint32_t value);

    uint32_t* pix_buf;
    uint32_t pix_buf_size;

    SDL_GPUTransferBuffer* _g_tbhdl;
    SDL_GPUTexture* _g_imthdl;
    SDL_GPUTextureTransferInfo _g_t_ti;
    SDL_GPUTextureRegion _g_tt;
};