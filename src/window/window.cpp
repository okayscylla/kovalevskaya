#include "window/window.h"

#include <SDL3/SDL.h>
#include <iostream>


void KovWindow::init(int w, int h, std::string title, int t_fpss) {
    width = w; height = h; window_title = title;

    SDL_Init(SDL_INIT_VIDEO);

    _sdlwindow = SDL_CreateWindow(title.c_str(), width, height, 0);

    _sdlsfmts = SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL;

    _sdlhgpu = SDL_CreateGPUDevice(
        _sdlsfmts,
        false,
        NULL
    );

    SDL_ClaimWindowForGPUDevice(_sdlhgpu, _sdlwindow);
    SDL_SetGPUSwapchainParameters(
        _sdlhgpu,
        _sdlwindow,
        SDL_GPU_SWAPCHAINCOMPOSITION_SDR,
        SDL_GPU_PRESENTMODE_IMMEDIATE
    );

    setTargetFPS(t_fpss);

    kb_state = SDL_GetKeyboardState(NULL);
}

void KovWindow::setTitle(std::string title) {
    window_title = title;

    SDL_SetWindowTitle(_sdlwindow, window_title.c_str());
}

void KovWindow::resize(int w, int h) {
    width = w; height = h;

    SDL_SetWindowSize(_sdlwindow, width, height);

    renderer->init(_sdlhgpu, width, height);
}

void KovWindow::setTargetFPS(int fps) {
    _target_ft = SDL_SECONDS_TO_NS((uint64_t)(1 / 480));
}

void KovWindow::poll() {
    while (SDL_PollEvent(_sdlevent)) {
        switch (_sdlevent->type) {
            case SDL_EVENT_QUIT:
                gracefulExit();
                break;
            default: break;
        }
    }
};

void KovWindow::setRenderer(Renderer* new_renderer) {
    renderer->cleanup();
    delete renderer;

    renderer->init(_sdlhgpu, width, height);
    renderer = new_renderer;
}

void KovWindow::draw() {
    renderer->draw(nullptr);

    curr_frame += 1;
}

void KovWindow::gracefulExit() {
    renderer->cleanup();

    SDL_ReleaseWindowFromGPUDevice(_sdlhgpu, _sdlwindow);
    SDL_DestroyWindow(_sdlwindow);
    SDL_DestroyGPUDevice(_sdlhgpu);

    SDL_Quit();

    delete _sdlevent;
    delete renderer;

    _quit = true;
}

void KovWindow::exit() { _quit = true; }

void KovWindow::mainloop() {
    while (!_quit) {
        uint64_t f_start = SDL_GetTicksNS();

        poll();
        draw();

        uint64_t f_end = SDL_GetTicksNS();
        _real_ft = f_end - f_start;

        if (_real_ft < _target_ft) {
            SDL_DelayNS(_target_ft - _real_ft);
        }
    }
}

const void KovWindow::log(std::string message) {
    std::cout << "KOV: " << message << std::endl;
}