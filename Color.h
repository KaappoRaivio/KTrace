//
// Created by kaappo on 10.9.2021.
//
#pragma once

#include <array>

class Color {
protected:
    double m_gamma;
    double m_r, m_g, m_b;

public:
    Color (double r, double g, double b, double gamma);
    Color (const Color& other) = default;
    Color (Color&& original) noexcept;
    Color& operator=(Color&& original) noexcept;

    [[nodiscard]] Color changeGamma(double new_gamma) const;

    [[nodiscard]] double gamma() const;
    [[nodiscard]] double r() const;
    [[nodiscard]] double g() const;
    [[nodiscard]] double b() const;

    friend std::ostream& operator<<(std::ostream & ostream, const Color & color);

    Color operator* (double color) const;
};

std::ostream& operator<<(const Color & color, std::ostream & ostream);
