#include <iostream>
#include "MyOpenGLWindow.h"
#include "Color.h"

int main () {
    std::cout << "Hello, World!" << std::endl;
    MyOpenGLWindow window{640, 480, 2.2};

    Color color(0.5, 1.0, 1.0, 2.0);
    std::cout << color.changeGamma(1.0) << std::endl;

    for (int y = 0; y < 100; y++) {
        for (int x = 0; x < 100; x++) {
            window.set_pixel(x, y, color);

        }
    }
    window.update();


    window.delay(3000);
    SDL_Quit();
    return 0;
}
