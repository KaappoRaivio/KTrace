//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <ostream>
#include "Vector3.h"

class Ray {
public:
    Ray(const Vector3 &origin, const Vector3 &direction);

private:
    Vector3 origin;
    Vector3 direction;

public:
    [[nodiscard]] const Vector3 &getOrigin() const;
    [[nodiscard]] const Vector3 &getDirection() const;
    [[nodiscard]] Vector3 apply (double lambda) const;

    friend std::ostream &operator<<(std::ostream &os, const Ray &ray);
};


