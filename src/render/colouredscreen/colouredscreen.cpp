#include "render/colouredscreen/colouredscreen.h"


void ColouredScreen::draw() {
    SDL_GPUCommandBuffer* _cmdbuf;
    _cmdbuf = SDL_AcquireGPUCommandBuffer(_hdlgpu);

    SDL_GPUTexture* _swapchain_texture;
    SDL_WaitAndAcquireGPUSwapchainTexture(
        _cmdbuf, _hdlwindow,
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
    _rpass = SDL_BeginGPURenderPass(_cmdbuf, &t_info, 1, NULL);
    SDL_EndGPURenderPass(_rpass);

    SDL_SubmitGPUCommandBuffer(_cmdbuf);
}