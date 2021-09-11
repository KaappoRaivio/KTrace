//
// Created by kaappo on 10.9.2021.
//
#pragma once

#include <array>

class Color {
private:
    const double m_gamma;
    const double m_r, m_g, m_b;

public:
    Color (double r, double g, double b, double gamma);

    [[nodiscard]] Color changeGamma(double new_gamma) const;

    [[nodiscard]] const double gamma() const;
    [[nodiscard]] const double r() const;
    [[nodiscard]] const double g() const;
    [[nodiscard]] const double b() const;

    friend std::ostream& operator<<(std::ostream & ostream, const Color & color);
};

std::ostream& operator<<(const Color & color, std::ostream & ostream);
