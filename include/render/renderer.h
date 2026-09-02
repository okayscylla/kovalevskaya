#pragma 

#include <SDL3/SDL.h>
#include <cstdint>

class Renderer {
    public:
    void virtual init(SDL_GPUDevice* hdlgpu, int w, int h);
    void virtual cleanup();

    void virtual draw(uint32_t* b);

    protected:
    void virtual setPixel();

    SDL_GPUDevice* gpu;
};