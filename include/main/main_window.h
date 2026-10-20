#pragma once

#include "window/window.h"
#include "types/scene/world.h"
#include "types/scene/camera.h"


class KovSceneViewer : public KovWindow {
    public:
    World world; // TODO: maybe move these out of KovWindow to make window library more independent?
    Camera camera; // TODO: support multible cameras

    void init(int w = 1080, int h = 720, std::string title = "KovWindow", int t_fps = 480, World* _world, Camera* _camera);
    void setRenderer(Renderer* new_renderer);
}