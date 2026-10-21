#include "window/main.h"
#include "main/main_window.h"

#include "utils/macros.h"

#include "types/primitives/sphere.h"
#include "types/primitives/plane.h"
#include "types/scene/light.h"

#include <cmath>


int main() {
    KovSceneViewer window = KovSceneViewer();

    World world = World();

    world.addObject(
        new Sphere(
            -1,
            Material(Colour(1,0,0))
        )
    );

    // world.addObject(
    //     new Sphere(
    //         -1,
    //         Material(Colour(0.5,0.5,0),0.1,0.9,0.9,600)
    //     )
    // );

    world.addObject(
        new Sphere(
            -1
        )
    );

    world.atID(0)->transform(Translate(0, 1, 2));
    // world.atID(1)->transform(Translate(0, 2.5, 0));
    // world.atID(1)->transform(Scale(1, 0.5, 1));
    // world.atID(1)->transform(RotateY(PI / 8));
    world.atID(1)->transform(Scale(99, 0.05, 99));

    // world.addLight(
    //     new PointLight(
    //         Point(-10,11,10)
    //     )
    // );

    world.addLight(
        new PointLight(
            Point(-5,6,8)
        )
    );

    Camera camera = Camera(1080, 720, degToRad(95.f));

    camera.transform(Translate(0, 0, 0));

    window.init(1080, 720, "KovSceneViewer", 15, &world, &camera);

    window.mainloop();

    return 0;
}