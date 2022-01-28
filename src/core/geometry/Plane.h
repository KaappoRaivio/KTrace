//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <optional>
#include "../common/MyVector3.h"
#include "Ray.h"
#include "Surface.h"

class Plane : public Surface {
private:
    MyVector3 normal;
    double intersect;
public:
    Plane (MyVector3 normal, double intersect);

    static Plane from_three_points (const MyVector3& t1, const MyVector3& t2, const MyVector3& t3);

    bool includes (const MyVector3& vector) const;

    double get_intersection_distance (const Ray& ray) const override;


    MyVector3 get_normal_at (const MyVector3& position) const override;

    MyVector3 get_uv_at (const MyVector3& position) const override;

    const MyVector3& getNormal () const;

    double getIntersect () const;
};



