#pragma once

#include <SDL3/SDL.h>


class Renderer {
    public:
    void virtual init(SDL_GPUDevice* gpu, SDL_Window* window, int w, int h);
    void virtual cleanup();

    void virtual draw();

    protected:
    int width, height;
    SDL_GPUDevice* _hdlgpu;
    SDL_Window* _hdlwindow;
};