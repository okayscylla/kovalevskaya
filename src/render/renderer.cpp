#include "render/renderer.h"


void Renderer::init(SDL_GPUDevice* gpu, SDL_Window* window, int w, int h) {
    _hdlgpu = gpu; _hdlwindow = window;

    width = w; height = h;
}

void Renderer::cleanup() { return; }

void Renderer::draw() {
    SDL_GPUCommandBuffer* _g_cmdbuf;
    _g_cmdbuf = SDL_AcquireGPUCommandBuffer(_hdlgpu);

    SDL_GPUTexture* _g_swapchain_texture;
    SDL_WaitAndAcquireGPUSwapchainTexture(
        _g_cmdbuf, _hdlwindow,
        &_g_swapchain_texture,
        NULL, NULL
    );

    SDL_GPUColorTargetInfo _g_t_info = {
        .texture = _g_swapchain_texture,
        .clear_color = {0.831373f, 1.0f, 0.972549f, 1.0f},
        .load_op = SDL_GPU_LOADOP_CLEAR,
        .store_op = SDL_GPU_STOREOP_STORE,
        .cycle = true
    };

    SDL_GPURenderPass* _g_rpass;
    _g_rpass = SDL_BeginGPURenderPass(_g_cmdbuf, &_g_t_info, 1, NULL);
    SDL_EndGPURenderPass(_g_rpass);

    SDL_SubmitGPUCommandBuffer(_g_cmdbuf);
}