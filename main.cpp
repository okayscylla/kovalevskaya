#include <SDL3/SDL_main.h>

#include "window/window.h"


int main() {
    KovWindow window = KovWindow();

    window.init();
    window.mainloop();

    return 0;
}