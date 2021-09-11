//
// Created by kaappo on 10.9.2021.
//
#pragma once

#include <SDL2/SDL.h>
#include "Color.h"

class MyOpenGLWindow {
private:
    inline static bool initialized;

    int m_width;
    int m_height;
    double m_gamma;

    SDL_Window *window;
    SDL_Renderer *renderer;
public:
    MyOpenGLWindow(int width, int height, double gamma);
    ~MyOpenGLWindow();

    void set_pixel (int x, int y, const Color& color);
    void update ();
    void delay(int millis);
};

