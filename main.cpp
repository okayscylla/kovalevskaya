#include "window/main.h"
#include "main/main_window.h"

#include "utils/macros.h"

#include "types/primitives/sphere.h"
#include "types/scene/light.h"

#include "render/raytracer/raytracer.h"


int main() {
    KovSceneViewer window = KovSceneViewer();

    World world = World();
    world.addLight(new PointLight(Point(-10,10,-10)));

    world.addObject(new Sphere(-1, Material(Colour(0.8,1.0,0.6),0.1,0.7,0.2,200)));

    Camera camera = Camera(1080, 720, PI / 2);

    camera.transform(Translate(0, 0, -4));

    window.init(1080, 720, "KovSceneViewer", 480, &world, &camera);
    window.setRenderer(new RayTracer);

    window.mainloop();

    return 0;
}