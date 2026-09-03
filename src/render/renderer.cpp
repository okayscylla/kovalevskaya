#include "render/renderer.h"


void Renderer::init(SDL_GPUDevice* gpu, SDL_Window* window, int w, int h) {
    _hdlgpu = gpu; _hdlwindow = window;

    width = w; height = h;
}

void Renderer::cleanup() { return; }

void Renderer::draw() {
    _hdlcmdbuf = SDL_AcquireGPUCommandBuffer(_hdlgpu);

    SDL_WaitAndAcquireGPUSwapchainTexture(
        _hdlcmdbuf, _hdlwindow,
        &_swapchain_texture,
        NULL, NULL
    );

    SDL_GPUColorTargetInfo t_info = {
        .texture = _swapchain_texture,
        .clear_color = {0.831373f, 1.0f, 0.972549f, 1.0f},
        .load_op = SDL_GPU_LOADOP_CLEAR,
        .store_op = SDL_GPU_STOREOP_STORE,
        .cycle = true
    };

    SDL_GPURenderPass* _rpass;
    _rpass = SDL_BeginGPURenderPass(_hdlcmdbuf, &t_info, 1, NULL);
    SDL_EndGPURenderPass(_rpass);

    SDL_SubmitGPUCommandBuffer(_hdlcmdbuf);
}