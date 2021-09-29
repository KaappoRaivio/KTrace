//
// Created by kaappo on 13.9.2021.
//

#pragma once


class Color {
private:
    const double r, g, b;
    const double gamma;
public:
    Color (double r, double g, double b, double gamma);

    double getR () const;

    double getG () const;

    double getB () const;

    double getGamma () const;
};



