//
// Created by kaappo on 10.9.2021.
//
#pragma once

#include <array>
#include <ostream>
#include <glm/vec3.hpp>
#include "Intensity.h"
#include "Color.h"

class Intensity {
protected:
    double m_r, m_g, m_b;

public:
    constexpr Intensity (double r, double g, double b) : m_r{r}, m_g{g}, m_b{b} {};
    constexpr Intensity () : Intensity{0, 0, 0} {};

//    Intensity (const Intensity& other) = default;
//    Intensity (Intensity&& original) noexcept;
//    Intensity& operator=(Intensity&& original) noexcept;

    double r () const;

    double g () const;

    double b () const;

    friend std::ostream& operator<< (std::ostream& ostream, const Intensity& color);

    Intensity operator* (double coeff) const;

    Intensity operator/ (double coeff) const;

    Intensity operator* (const Intensity& other) const;

    Intensity operator+ (const Intensity& other) const;

    Intensity operator+= (const Intensity& other);

    Color applyGamma (double d) const;
    glm::vec3 asRGB (double gamma) const;
};

std::ostream& operator<< (const Intensity& color, std::ostream& ostream);

namespace Intensities {
    constexpr Intensity INCANDESCENT {244 / 256.0,175 / 256.0,90 / 256.0};
    constexpr Intensity INCANDESCENT_2 {244 / 256.0,175 / 256.0,120 / 256.0};
}