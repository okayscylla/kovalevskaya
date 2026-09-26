#include "render/colouredscreen/colouredscreen.h"

#include "types/colour.h"

#include <cstdlib>


void ColouredScreen::init(SDL_GPUDevice* gpu, SDL_Window* window, int w, int h) {
    _hdlgpu = gpu; _hdlwindow = window;

    width = w; height = h;

    pix_buf_size = w * h * sizeof(uint32_t);

    pix_buf = (uint32_t*)malloc(pix_buf_size);

    SDL_GPUTextureCreateInfo _g_t_ci = {
        .type = SDL_GPU_TEXTURETYPE_2D,
        .format = SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,
        .usage = SDL_GPU_TEXTUREUSAGE_SAMPLER,
        .width = static_cast<uint32_t>(width),
        .height = static_cast<uint32_t>(height),
        .layer_count_or_depth = 1,
        .num_levels = 1
    };

    _g_imthdl = SDL_CreateGPUTexture(
        _hdlgpu,
        &_g_t_ci
    );

    SDL_GPUTransferBufferCreateInfo _g_tb_ci = {
        .usage = SDL_GPU_TRANSFERBUFFERUSAGE_UPLOAD,
        .size = SDL_CalculateGPUTextureFormatSize(SDL_GPU_TEXTUREFORMAT_R8G8B8A8_UNORM,width,height,1)
    };

    _g_tbhdl = SDL_CreateGPUTransferBuffer(_hdlgpu, &_g_tb_ci);

    _g_t_ti = {
        .transfer_buffer = _g_tbhdl,
        .offset = 0
    };

    _g_tt = {
        .texture = _g_imthdl,
        .w = static_cast<uint32_t>(width),
        .h = static_cast<uint32_t>(height),
        .d = 1
    };
}

void ColouredScreen::draw() {
    SDL_GPUCommandBuffer* _g_cmdbuf;
    _g_cmdbuf = SDL_AcquireGPUCommandBuffer(_hdlgpu);

    SDL_GPUTexture* _g_swapchain_texture;
    SDL_WaitAndAcquireGPUSwapchainTexture(
        _g_cmdbuf, _hdlwindow,
        &_g_swapchain_texture,
        NULL, NULL
    );

    writePixel(500, 500, Colour(1,1,1).toInt()); // A B G R

    void* _g_tbloc = SDL_MapGPUTransferBuffer(_hdlgpu, _g_tbhdl, true);

    memcpy(_g_tbloc, pix_buf, pix_buf_size);

    SDL_UnmapGPUTransferBuffer(_hdlgpu, _g_tbhdl);

    SDL_GPUCopyPass* _g_gcp = SDL_BeginGPUCopyPass(_g_cmdbuf);

    SDL_UploadToGPUTexture(_g_gcp, &_g_t_ti, &_g_tt, true);

    SDL_EndGPUCopyPass(_g_gcp);

    SDL_GPUColorTargetInfo _g_t_info = {
        .texture = _g_swapchain_texture,
        .clear_color = {0.831373f, 1.0f, 0.972549f, 1.0f},
        .load_op = SDL_GPU_LOADOP_CLEAR,
        .store_op = SDL_GPU_STOREOP_STORE,
        .cycle = true
    };

    SDL_GPURenderPass* _g_rpass = SDL_BeginGPURenderPass(_g_cmdbuf, &_g_t_info, 1, NULL);

    SDL_EndGPURenderPass(_g_rpass);

    SDL_GPUBlitInfo _g_gbi = {
        .source.texture = _g_imthdl,
        .source.w = static_cast<uint32_t>(width),
        .source.h = static_cast<uint32_t>(height),
        .destination.texture = _g_swapchain_texture,
        .destination.w = static_cast<uint32_t>(width),
        .destination.h = static_cast<uint32_t>(height),
        .load_op = SDL_GPU_LOADOP_DONT_CARE,
        .filter = SDL_GPU_FILTER_NEAREST
    };

    SDL_BlitGPUTexture(
        _g_cmdbuf,
        &_g_gbi
    );

    SDL_SubmitGPUCommandBuffer(_g_cmdbuf);
}

void ColouredScreen::cleanup() {
    SDL_ReleaseGPUTexture(_hdlgpu, _g_imthdl);
}

void ColouredScreen::writePixel(int x, int y, uint32_t value) {
    pix_buf[y * width  + x] = value;
}