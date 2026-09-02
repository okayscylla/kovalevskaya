#include "render/renderer.h"


void Renderer::init(SDL_GPUDevice* gpu, SDL_Window* window, int w, int h) {
    _hdlgpu = gpu; _hdlwindow = window;

    width = w; height = h;
}

void Renderer::cleanup() { return; }

void Renderer::draw() {
    SDL_GPUCommandBuffer* _cmdbuf;
    _cmdbuf = SDL_AcquireGPUCommandBuffer(_hdlgpu);

    SDL_GPUTexture* swapchain_texture;
    SDL_WaitAndAcquireGPUSwapchainTexture(
        _cmdbuf, _hdlwindow,
        &swapchain_texture,
        NULL, NULL
    );

    SDL_GPUColorTargetInfo t_info = {
        .texture = swapchain_texture,
        .clear_color = {0.831373f, 1.0f, 0.972549f, 1.0f},
        .load_op = SDL_GPU_LOADOP_CLEAR,
        .store_op = SDL_GPU_STOREOP_STORE,
        .cycle = true
    };

    SDL_GPURenderPass* _rpass;
    _rpass = SDL_BeginGPURenderPass(_cmdbuf, &t_info, 1, NULL);
    SDL_EndGPURenderPass(_rpass);

    SDL_SubmitGPUCommandBuffer(_cmdbuf);
}