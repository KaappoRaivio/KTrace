//
// Created by kaappo on 11.9.2021.
//

#pragma once

#include <optional>
#include <ostream>

#include "../common/MyVector3.h"
#include "Plane.h"
#include "Surface.h"

class Triangle : public Surface {
private:
    MyVector3 t1, t2, t3;
    MyVector3 tu, tv, tw;

    Plane plane;

    bool includes (const MyVector3& vector) const;
    bool check_bounds (const MyVector3& vector) const;
public:
    Triangle (const MyVector3& t1, const MyVector3& t2, const MyVector3& t3, const Material* material, const MyVector3& texture1, const MyVector3& texture2, const MyVector3& texture3);
    Triangle (const MyVector3& t1, const MyVector3& t2, const MyVector3& t3, const Material* material);
    double getIntersectionDistance (const Ray& ray, const Surface*& hitSurface, const Material*& hitMaterial) const override;

    MyVector3 getNormalAt (const MyVector3& position) const override;
    MyVector3 getUVAt (const MyVector3& position) const override;

    AABB getBoundingBox () const override;

    const Material* getMaterial () const override;

    friend std::ostream& operator<< (std::ostream& os, const Triangle& triangle);

};


//extern const double PRECISION_LIMIT = 0.001;
//
//int main () {
//    Triangle triangle = {MyVector3{-5, 6, 5}, {0, 0, 3}, {5, 6, 3}};
//    std::cout << triangle.getUVAt({4.01, 5.46, 3.11}) << std::endl;
//    std::cout << triangle.getUVAt({-1.95, 2.72, 3.84}) << std::endl;
////    std::cout << "done" << std::endl;
//}
