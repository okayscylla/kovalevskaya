#pragma once

#include "render/renderer.h"

#include <SDL3/SDL.h>
#include <string>


class KovWindow {
    public:
    void virtual init(int w = 1080, int h = 720, std::string title = "KovWindow", int t_fps = 480);
    void setTitle(std::string title);
    void resize(int w, int h);
    void setTargetFPS(int fps);

    void virtual poll();

    void setRenderer(Renderer* new_renderer);
    void draw();

    void virtual gracefulExit();
    void exit();

    void virtual mainloop();

    int width, height;
    std::string window_title;

    protected:
    Renderer* renderer = nullptr;
    const bool* kb_state;
    int curr_frame;

    private:
    bool _quit = false;
    uint64_t _target_ft;

    SDL_GPUShaderFormat _sdlsfmts;
    SDL_GPUTextureCreateInfo _sdlgputinfo;

    SDL_Event* _sdlevent = new SDL_Event;
    SDL_Window* _sdlwindow;
    SDL_GPUDevice* _sdlhgpu;
};