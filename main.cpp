#include "window/main.h"
#include "main/main_window.h"


int main() {
    KovSceneViewer window = KovSceneViewer();

    window.init(int w = 1080, int h = 720, std::string title = "KovSceneViewer", int t_fps = 480, new DefaultWorld, new Camera);
    window.setRender(new RayTracer);

    window.mainloop();

    return 0;
}