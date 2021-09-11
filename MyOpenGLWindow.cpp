//
// Created by kaappo on 10.9.2021.
//

#include <iostream>
#include "MyOpenGLWindow.h"

MyOpenGLWindow::MyOpenGLWindow(int width, int height, double gamma) : m_width{width}, m_height{height}, m_gamma{gamma} {
    if (!MyOpenGLWindow::initialized) {
        SDL_Init(SDL_INIT_VIDEO);
        MyOpenGLWindow::initialized = true;
    }

    window = SDL_CreateWindow(
            "An SDL2 window",                  //    window title
            SDL_WINDOWPOS_UNDEFINED,           //    initial x position
            SDL_WINDOWPOS_UNDEFINED,           //    initial y position
            m_width,                               //    m_width, in pixels
            m_height,                               //    m_height, in pixels
            SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL //    flags - see below
    );

    if (window == nullptr){
        // In the event that the window could not be made...
        std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
        throw std::runtime_error("SDL initialization error!");
    }

    SDL_CreateWindowAndRenderer(m_width, m_height, 0, &window, &renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
//    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
//    for (int i = 0; i < m_height; ++i)
//        SDL_RenderDrawPoint(renderer, i, i);
//    SDL_RenderPresent(renderer);
}

void MyOpenGLWindow::set_pixel(int x, int y, const Color &color) {
    auto gamma_corrected = color.changeGamma(m_gamma);
    auto r = (uint8_t)(gamma_corrected.r() * 256.0);
    auto g = (uint8_t)(gamma_corrected.g() * 256.0);
    auto b = (uint8_t)(gamma_corrected.b() * 256.0);

    std::cout << unsigned(r) << std::endl;

    SDL_SetRenderDrawColor(renderer, r, g, b, 1.0);
    SDL_RenderDrawPoint(renderer, x, y);
}

void MyOpenGLWindow::update() {
    SDL_RenderPresent(renderer);
}

void MyOpenGLWindow::delay(int millis) {
    SDL_Delay(millis);  // Pause execution for 3000 milliseconds, for example
}

MyOpenGLWindow::~MyOpenGLWindow() {
    std::cout << "closing!" << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

