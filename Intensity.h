//
// Created by kaappo on 10.9.2021.
//
#pragma once

#include <array>
#include <ostream>
#include "Intensity.h"
#include "Color.h"

class Intensity {
protected:
    double m_r, m_g, m_b;

public:
    Intensity (double r, double g, double b);
    Intensity (const Intensity& other) = default;
    Intensity (Intensity&& original) noexcept;
    Intensity& operator=(Intensity&& original) noexcept;

    [[nodiscard]] double r() const;
    [[nodiscard]] double g() const;
    [[nodiscard]] double b() const;

    friend std::ostream& operator<<(std::ostream & ostream, const Intensity & color);

    Intensity operator* (double coeff) const;
    Intensity operator* (const Intensity& other) const;
    Intensity operator+ (const Intensity& other) const;
    Intensity operator+=(const Intensity& other);

    [[nodiscard]] Color applyGamma(double d) const;
};

std::ostream& operator<<(const Intensity & color, std::ostream & ostream);
