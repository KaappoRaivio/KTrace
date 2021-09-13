//
// Created by kaappo on 10.9.2021.
//
#include <iostream>
#include <cmath>

#include "Color.h"


Color::Color(double r, double g, double b, double gamma=1) : m_r{r}, m_g{g}, m_b{b}, m_gamma{gamma} {}
Color::Color(Color &&original) noexcept: m_r{original.r()}, m_g{original.g()}, m_b{original.b()}, m_gamma(original.gamma()) {}
Color &Color::operator=(Color &&original) noexcept {
    m_r = original.r();
    m_b = original.g();
    m_b = original.b();
    m_gamma = original.gamma();
    return *this;
}

std::ostream& operator<<(std::ostream & ostream, const Color& color) {
    return ostream << "Color(" << color.m_r << ", " << color.m_g << ", " << color.m_b << ", " << color.m_gamma << ")";
}

Color Color::changeGamma(double new_gamma) const {
    if (gamma() == 1 && new_gamma == 1) {
        return *this;
    } else {
        return {pow(m_r, m_gamma / new_gamma), pow(m_g, m_gamma / new_gamma), pow(m_b, m_gamma / new_gamma), new_gamma};
    }
}

double Color::gamma() const {
    return m_gamma;
}

double Color::r() const {
    return m_r;
}

double Color::g() const {
    return m_g;
}

double Color::b() const {
    return m_b;
}

Color Color::operator*(double coeff) const {
    const Color &temp = changeGamma(1);
    return {temp.r() * coeff, temp.g() * coeff, temp.b() * coeff, 1};
}

