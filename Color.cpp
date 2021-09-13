//
// Created by kaappo on 13.9.2021.
//

#include "Color.h"

Color::Color(double r, double g, double b, double gamma) : r(r), g(g), b(b), gamma{gamma} {}

double Color::getR() const {
    return r;
}

double Color::getG() const {
    return g;
}

double Color::getB() const {
    return b;
}

double Color::getGamma() const {
    return gamma;
}
