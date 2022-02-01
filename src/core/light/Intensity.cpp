//
// Created by kaappo on 10.9.2021.
//
#include <iostream>
#include <cmath>

#include "Intensity.h"
#include "Intensity.h"



//Intensity::Intensity(Intensity &&original) noexcept: m_r{original.r()}, m_g{original.g()}, m_b{original.b()} {}
//Intensity &Intensity::operator=(Intensity &&original) noexcept {
//    m_r = original.r();
//    m_g = original.g();
//    m_b = original.b();
//    return *this;
//}

std::ostream& operator<< (std::ostream& ostream, const Intensity& color) {
    return ostream << "Intensity(" << color.m_r << ", " << color.m_g << ", " << color.m_b << ")";
}

double Intensity::r () const {
    return m_r;
}

double Intensity::g () const {
    return m_g;
}

double Intensity::b () const {
    return m_b;
}

Intensity Intensity::operator* (double coeff) const {
    return {r() * coeff, g() * coeff, b() * coeff};
}

Intensity Intensity::operator* (const Intensity& other) const {
    return {r() * other.r(), g() * other.g(), b() * other.b()};
}

Intensity Intensity::operator+ (const Intensity& other) const {
    return {r() + other.r(), g() + other.g(), b() + other.b()};
}

Intensity Intensity::operator+= (const Intensity& other) {
    m_r += other.r();
    m_g += other.g();
    m_b += other.b();
    return *this;
}

Color Intensity::applyGamma (double gamma) const {
    return {pow(r(), 1.0 / gamma), pow(g(), 1.0 / gamma), pow(b(), 1.0 / gamma), gamma};
}

Intensity Intensity::operator/ (double coeff) const {
    return *this * (1 / coeff);
}

