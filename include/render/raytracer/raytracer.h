#pragma once

#include "render/renderer.h"

#include "types/scene/world.h"
#include "types/scene/camera.h"

#include <cstdint>


class RayTracer : public Renderer {
    public:
    void init(SDL_GPUDevice* gpu, SDL_Window* window, int w, int h, World* _world, Camera* _camera);
    void cleanup();

    void draw();
    void renderFrame();

    private:
    void writePixel(int x, int y, uint32_t value);

    uint32_t* pix_buf;
    uint32_t pix_buf_size;

    World* world;
    Camera* camera;

    SDL_GPUTransferBuffer* _g_tbhdl;
    SDL_GPUTexture* _g_imthdl;
    SDL_GPUTextureTransferInfo _g_t_ti;
    SDL_GPUTextureRegion _g_tt;
};