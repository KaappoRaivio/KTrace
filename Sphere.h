//
// Created by kaappo on 14.9.2021.
//

#pragma once


#include "Surface.h"

class Sphere : public Surface {
private:
    MyVector3 center;
    double radius;
public:
    Sphere (MyVector3 center, double radius);

private:

    bool includes (const MyVector3& point) const;

public:
    double get_intersection_distance (const Ray& ray) const override;

    MyVector3 get_normal_at (const MyVector3& position) const override;

    MyVector3 get_uv_at (const MyVector3& position) const override;
};



