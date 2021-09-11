//
// Created by kaappo on 10.9.2021.
//
#include <iostream>
#include <cmath>

#include "Color.h"


Color::Color(double r, double g, double b, double gamma=1) : m_r{r}, m_g{g}, m_b{b}, m_gamma{gamma} {}

std::ostream& operator<<(std::ostream & ostream, const Color& color) {
    return ostream << "Color(" << color.m_r << ", " << color.m_g << ", " << color.m_b << ", " << color.m_gamma << ")";
}

Color Color::changeGamma(double new_gamma) const {
    return (Color) {pow(m_r, 1.0 / m_gamma), pow(m_g, 1.0 / m_gamma), pow(m_b, 1.0 / m_gamma), new_gamma};
}

const double Color::gamma() const {
    return m_gamma;
}

const double Color::r() const {
    return m_r;
}

const double Color::g() const {
    return m_g;
}

const double Color::b() const {
    return m_b;
}

