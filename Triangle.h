//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include "Vector3.h"
#include "Plane.h"
#include "Surface.h"

class Triangle : Surface {
private:
    Vector3 t1, t2, t3;
    Plane plane;

    [[nodiscard]] bool includes (const Vector3 &vector) const;
    [[nodiscard]] bool check_bounds (const Vector3 &vector) const;
public:
    [[nodiscard]] double get_intersection_distance(const Ray &ray) const override;
    Triangle(const Vector3 &t1, const Vector3 &t2, const Vector3 &t3);

    Triangle(std::initializer_list<Vector3> list);
};



