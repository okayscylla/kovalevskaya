#include "main/sceneviewer.h"

#include "render/raytracer/raytracer.h"

#include "types/scene/world.h"
#include "types/scene/camera.h"


void KovSceneViewer::init(int w = 1080, int h = 720, std::string title = "KovWindow", int t_fps = 480, World* _world, Camera* _camera) {
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

    setTargetFPS(t_fpss);

    setRenderer(new RayTracer); // FIXME: find a better default?

    kb_state = SDL_GetKeyboardState(NULL); // FIXME: is this even necessary?
}

void KovSceneViewer::setRenderer(Renderer* new_renderer) {
    if (renderer != nullptr) {
        renderer->cleanup();
        klog("destroyed renderer\n");
        delete renderer;
    }

    renderer = new_renderer;

    renderer->init(_sdlhgpu, _sdlwindow, width, height, &world, &camera);
    klog("created new renderer\n");
}