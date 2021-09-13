//
// Created by kaappo on 10.9.2021.
//

#include <iostream>
#include "MyOpenGLWindow.h"

MyOpenGLWindow::MyOpenGLWindow(int width, int height, double gamma, int scale) : m_width{width}, m_height{height}, m_gamma{gamma}, scale{scale} { // NOLINT(cppcoreguidelines-pro-type-member-init)
    std::cout << "creating window" << std::endl;
    if (!MyOpenGLWindow::initialized) {
        SDL_Init(SDL_INIT_VIDEO);
        MyOpenGLWindow::initialized = true;
    }

    SDL_CreateWindowAndRenderer(m_width, m_height, 0, &window, &renderer);
    SDL_SetWindowTitle(window, "Raytracer");

    if (window == nullptr || renderer == nullptr){
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        throw std::runtime_error("SDL initialization error!");
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
    SDL_RenderClear(renderer);
}

void MyOpenGLWindow::set_pixel(int x, int y, const Intensity &color) const {
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

void MyOpenGLWindow::update() const {
    SDL_RenderPresent(renderer);
}

void MyOpenGLWindow::delay(int millis) {
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


    SDL_Delay(millis);
}

MyOpenGLWindow::~MyOpenGLWindow() {
    std::cout << "closing!" << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void MyOpenGLWindow::paint(std::vector<std::vector<Intensity>> pixels) const {
    for (int y = 0; y < pixels.size(); ++y) {
        for (int x = 0; x < pixels[y].size(); ++x) {
            set_pixel(x, y, pixels[y][x]);

        }
    }
    update();
}

