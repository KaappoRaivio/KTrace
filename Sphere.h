//
// Created by kaappo on 14.9.2021.
//

#pragma once


#include "Surface.h"

class Sphere : public Surface{
private:
    Vector3 center;
    double radius;
public:
    Sphere(Vector3 center, double radius);

private:

    [[nodiscard]] bool includes (const Vector3& point) const;
public:
    [[nodiscard]] double get_intersection_distance(const Ray &ray) const override;
    [[nodiscard]] Vector3 get_normal_at(const Vector3 &position) const override;
};



