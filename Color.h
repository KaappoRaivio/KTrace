//
// Created by kaappo on 13.9.2021.
//

#pragma once


class Color {
private:
    const double r, g, b;
    const double gamma;
public:
    Color(double r, double g, double b, double gamma);

    [[nodiscard]] double getR() const;
    [[nodiscard]] double getG() const;
    [[nodiscard]] double getB() const;
    [[nodiscard]] double getGamma() const;
};



