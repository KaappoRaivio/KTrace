//
// Created by kaappo on 11.9.2021.
//

#pragma once

#include <optional>

#include "Vector3.h"
#include "Plane.h"
#include "Surface.h"

class Triangle : public Surface {
private:
    Vector3 t1, t2, t3;
    Plane plane;

    [[nodiscard]] bool includes (const Vector3 &vector) const;
    [[nodiscard]] bool check_bounds (const Vector3 &vector) const;
public:
    [[nodiscard]] double get_intersection_distance(const Ray &ray) const override;
    [[nodiscard]] Vector3 get_normal_at(const Vector3 &position) const override;

    [[nodiscard]] Vector3 get_uv_at(const Vector3 &position) const override;

    Triangle(const Vector3 &t1, const Vector3 &t2, const Vector3 &t3);

    Triangle(std::initializer_list<Vector3> list);
};


//extern const double PRECISION_LIMIT = 0.001;
//
//int main () {
//    Triangle triangle = {Vector3{-5, 6, 5}, {0, 0, 3}, {5, 6, 3}};
//    std::cout << triangle.get_uv_at({4.01, 5.46, 3.11}) << std::endl;
//    std::cout << triangle.get_uv_at({-1.95, 2.72, 3.84}) << std::endl;
////    std::cout << "done" << std::endl;
//}
