#include "window/window.h"

#include "render/colouredscreen/colouredscreen.h"

#include <SDL3/SDL.h>
#include <iostream>
#include <cstdint>


void KovWindow::init(int w, int h, std::string title, int t_fpss) {
    width = w; height = h; window_title = title;

    SDL_Init(SDL_INIT_VIDEO);

    _sdlwindow = SDL_CreateWindow(title.c_str(), width, height, 0);

    _sdlsfmts = SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL;
    log(std::format("using shaderformat {}", _sdlsfmts));

    _sdlhgpu = SDL_CreateGPUDevice(
        _sdlsfmts,
        false,
        NULL
    );
    log("bound to gpu device");

    SDL_ClaimWindowForGPUDevice(_sdlhgpu, _sdlwindow);
    SDL_SetGPUSwapchainParameters(
        _sdlhgpu,
        _sdlwindow,
        SDL_GPU_SWAPCHAINCOMPOSITION_SDR,
        SDL_GPU_PRESENTMODE_IMMEDIATE
    );

    setTargetFPS(t_fpss);

    setRenderer(new ColouredScreen);

    kb_state = SDL_GetKeyboardState(NULL); // FIXME: is this even necessary?
}

void KovWindow::setTitle(std::string title) {
    window_title = title;

    SDL_SetWindowTitle(_sdlwindow, window_title.c_str());
    log(std::format("new title {}", title));
}

void KovWindow::resize(int w, int h) {
    width = w; height = h;

    SDL_SetWindowSize(_sdlwindow, width, height);

    renderer->init(_sdlhgpu, _sdlwindow, width, height);
    log(std::format("new resolution {}x{}", w, h));
}

void KovWindow::setTargetFPS(int fps) {
    _target_ft = 1000000000LL / fps;
    log(std::format("target frametime {}", _target_ft));
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
    if (renderer != nullptr) {
        renderer->cleanup();
        log(std::format("destroyed renderer id {}", renderer->id));
        delete renderer;
    }

    renderer = new_renderer;
    renderer->init(_sdlhgpu, _sdlwindow, width, height);
    log(std::format("using new renderer id {}", renderer->id));
}

void KovWindow::draw() {
    renderer->draw();

    curr_frame += 1;
}

void KovWindow::gracefulExit() {
    if (renderer != nullptr) {
        renderer->cleanup();
        log(std::format("destroyed renderer id {}", renderer->id));
        delete renderer;
    }

    SDL_ReleaseWindowFromGPUDevice(_sdlhgpu, _sdlwindow);
    SDL_DestroyWindow(_sdlwindow);
    SDL_DestroyGPUDevice(_sdlhgpu);

    SDL_Quit();
    
    delete _sdlevent;

    log("cleanup finished, exiting");

    _quit = true;
}

void KovWindow::exit() { _quit = true; }

void KovWindow::mainloop() {
    uint64_t f_end, f_deadline;

    f_deadline = SDL_GetTicksNS() + _target_ft;

    while (!_quit) {
        poll();
        draw();

        f_end = SDL_GetTicksNS();

        if (f_end < f_deadline) {
            SDL_DelayNS(f_deadline - f_end);
        } else {
            f_deadline = SDL_GetTicksNS();
        }

        f_deadline += _target_ft;
    }
}

const void KovWindow::log(std::string message) {
    std::cout << "KOV: " << message << std::endl;
}