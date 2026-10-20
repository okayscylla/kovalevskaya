#pragma once

#include <SDL3/SDL.h>

#include "types/scene/world.h"
#include "types/scene/camera.h"


class Renderer {
    public:
    void virtual init(SDL_GPUDevice* gpu, SDL_Window* window, int w, int h, World* _world = nullptr, Camera* _camera = nullptr);
    void virtual cleanup();

    void virtual draw();

    virtual ~Renderer() { cleanup(); }

    protected:
    int width, height;
    SDL_GPUDevice* _hdlgpu;
    SDL_Window* _hdlwindow;
};