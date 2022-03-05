//
// Created by kaappo on 10.9.2021.
//

#include <iostream>
#include "MyOpenGLWindow.h"
#include "../geometry/Ray.h"
#include "SDL2/SDL.h"

MyOpenGLWindow::MyOpenGLWindow (int width, int height, double gamma, int scale, const Camera& camera) : m_width{width}, m_height{height}, m_gamma{gamma}, scale{scale}, camera(camera) { // NOLINT(cppcoreguidelines-pro-type-member-init)
    std::cout << "creating window" << std::endl;
    if (!MyOpenGLWindow::initialized) {
        SDL_Init(SDL_INIT_VIDEO);
        MyOpenGLWindow::initialized = true;
    }

    int displays = SDL_GetNumVideoDisplays();

    // get display bounds for all displays
    std::vector<SDL_Rect> displayBounds;
    for (int i = 0 ; i < displays ; i++) {
        displayBounds.push_back(SDL_Rect());
        SDL_GetDisplayBounds(i, &displayBounds.back());
    }

// window of dimensions 500 * 500 offset 100 pixels on secondary monitor
    int x = displayBounds.back().x;
    int y = displayBounds.back().y;

//// so now x and y are on secondary display
//    SDL_Window* window = SDL_CreateWindow("title", x, y, w, h, FLAGS...);


    window = SDL_CreateWindow("Raytracer", x, y, width, height, SDL_WINDOW_BORDERLESS);
    renderer = SDL_CreateRenderer(window, 0, 0);
    SDL_SetWindowTitle(window, "Raytracer");

    if (window == nullptr || renderer == nullptr) {
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        throw std::runtime_error("SDL initialization error!");
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderClear(renderer);
    SDL_RaiseWindow(window);
}

void MyOpenGLWindow::set_pixel (int x, int y, const Intensity& color) const {
    constexpr auto epsilon = 1e-5;


    auto gamma_corrected = color.applyGamma(m_gamma);

    auto r = std::clamp((gamma_corrected.getR() * 256.0 - epsilon), 0.0, 256.0 - epsilon);
    auto g = std::clamp((gamma_corrected.getG() * 256.0 - epsilon), 0.0, 256.0 - epsilon);
    auto b = std::clamp((gamma_corrected.getB() * 256.0 - epsilon), 0.0, 256.0 - epsilon);

    SDL_SetRenderDrawColor(renderer, r, g, b, 1.0);

    SDL_Rect rect;
    rect.x = x * scale;
    rect.y = y * scale;
    rect.w = scale;
    rect.h = scale;
    SDL_RenderFillRect(renderer, &rect);
//    SDL_RenderDrawPoint(renderer, x, y);
}

void MyOpenGLWindow::update () const {
    SDL_RenderPresent(renderer);
}

void MyOpenGLWindow::delay (int millis) {
//    struct Container
//    {
//        static Uint32 TimerCallback( Uint32 interval, void* param )
//        {
//            SDL_Event event;
//            event.type = SDL_USEREVENT;
//            event.user.code = 42;
//            SDL_PushEvent( &event );
//            return 0;
//        }
//    };
//
//    SDL_AddTimer( millis, Container::TimerCallback, NULL );
//
//    SDL_Event event;
//    while( SDL_WaitEvent( &event ) )
//    {
//        if( event.type == SDL_USEREVENT && event.user.code == 42 )
//            break;
//    }

    SDL_Event event;

    double x = 0, y = 0;

    while (SDL_WaitEvent(&event)) {
        switch (event.type) {
            case SDL_MOUSEMOTION:
                x = event.motion.x;
                y = event.motion.y;
//                SDL_Delay();
                break;
            case SDL_MOUSEBUTTONUP:
                std::cout << "(" << x / scale << ", " << y / scale << "), corresponds to" << Ray{camera.getOrigin(), camera.get_viewplane(1)[y / scale][x / scale]} << std::endl;

                break;
        }
    }
}

MyOpenGLWindow::~MyOpenGLWindow () {
    std::cout << "closing!" << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void MyOpenGLWindow::paint (std::vector<std::vector<Intensity>> pixels) const {
    SDL_RenderClear(renderer);
    SDL_PumpEvents();
    for (size_t y = 0 ; y < pixels.size() ; ++y) {
        for (size_t x = 0 ; x < pixels[y].size() ; ++x) {
            set_pixel(x, y, pixels[y][x]);

        }
    }
    update();
}

