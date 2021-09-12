
//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include "Vector3.h"
#include "Ray.h"

class Plane {
private:
    Vector3 normal;
    double intersect;
public:
    Plane (const Vector3 &normal, double intersect);
    static Plane from_three_points (const Vector3& t1, const Vector3& t2, const Vector3& t3);

    [[nodiscard]] bool includes (const Vector3& vector) const;
    [[nodiscard]] double get_intersection_distance (const Ray& ray) const;
};



