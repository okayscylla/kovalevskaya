#include "main/main_window.h"

#include "render/raytracer/raytracer.h"

#include "types/scene/world.h"
#include "types/scene/camera.h"

#include "utils/macros.h"

#include <print>
#include <cmath>


void KovSceneViewer::init(int w, int h, std::string title, int t_fps, World* _world, Camera* _camera) {
    width = w; height = h; window_title = title;

    world = _world;
    camera = _camera;

    SDL_Init(SDL_INIT_VIDEO);

    _sdlwindow = SDL_CreateWindow(title.c_str(), width, height, 0);

    _sdlsfmts = SDL_GPU_SHADERFORMAT_MSL | SDL_GPU_SHADERFORMAT_SPIRV | SDL_GPU_SHADERFORMAT_DXIL | SDL_GPU_SHADERFORMAT_MSL;
    klog("using shaderformat {}\n", _sdlsfmts);

    SDL_SetHint(SDL_HINT_GPU_DRIVER, "vulkan"); // force vulkan rendering

    _sdlhgpu = SDL_CreateGPUDevice(
        _sdlsfmts,
        false,
        NULL
    );
    klog("bound to gpu device\n");

    SDL_ClaimWindowForGPUDevice(_sdlhgpu, _sdlwindow);
    SDL_SetGPUSwapchainParameters(
        _sdlhgpu,
        _sdlwindow,
        SDL_GPU_SWAPCHAINCOMPOSITION_SDR,
        SDL_GPU_PRESENTMODE_IMMEDIATE
    );

    SDL_SetWindowRelativeMouseMode(_sdlwindow, capture_mouse);

    setTargetFPS(t_fps);
    setRenderer(new RayTracer); // FIXME: find a better default?

    kb_state = SDL_GetKeyboardState(NULL); // FIXME: is this even necessary?
}

void KovSceneViewer::poll() {
    float rel_mx, rel_my;

    SDL_GetRelativeMouseState(&rel_mx, &rel_my);

    while (SDL_PollEvent(_sdlevent)) {
        switch (_sdlevent->type) {
            case SDL_EVENT_QUIT:
                gracefulExit();
                break;
            case SDL_EVENT_KEY_DOWN:
                switch (_sdlevent->key.scancode) {
                    case SDL_SCANCODE_UP: // should probably be checking keycode instead of scancode but i dont care enough
                        movement_speed *= 2;
                        break;
                    case SDL_SCANCODE_DOWN:
                        movement_speed /= 2;
                        break;
                    case SDL_SCANCODE_ESCAPE:
                        capture_mouse = !capture_mouse;

                        SDL_SetWindowRelativeMouseMode(_sdlwindow, capture_mouse);
                    default: break;
                }
            default: break;
        }
    }

    if (kb_state[SDL_SCANCODE_W]) { // FIXME: make this framerate independent
        camera->transform(Translate(0, 0, movement_speed));
    } if (kb_state[SDL_SCANCODE_S]) {
        camera->transform(Translate(0, 0, -movement_speed));
    } if (kb_state[SDL_SCANCODE_D]) {
        camera->transform(Translate(movement_speed, 0, 0));
    } if (kb_state[SDL_SCANCODE_A]) {
        camera->transform(Translate(-movement_speed, 0, -0));
    } if (kb_state[SDL_SCANCODE_SPACE]) {
        camera->transform(Translate(0, -movement_speed, 0));
    } if (kb_state[SDL_SCANCODE_LSHIFT]) {
        camera->transform(Translate(0, movement_speed, 0));
    }

    camera->transform(RotateY(rel_mx / 1000)); // TODO: make this work
    camera->transform(RotateX(rel_my / 1000)); // TODO: make this work
}

void KovSceneViewer::setRenderer(Renderer* new_renderer) {
    if (renderer != nullptr) {
        renderer->cleanup();
        klog("destroyed renderer\n");
        delete renderer;
    }

    renderer = new_renderer;

    renderer->init(_sdlhgpu, _sdlwindow, width, height, world, camera);
    klog("created new renderer\n");
}