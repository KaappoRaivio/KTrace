//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <optional>
#include "Vector3.h"
#include "Ray.h"
#include "Surface.h"

class Plane : public Surface {
private:
    Vector3 normal;
    double intersect;
public:
    Plane (Vector3 normal, double intersect);

    static Plane from_three_points (const Vector3& t1, const Vector3& t2, const Vector3& t3);

    bool includes (const Vector3& vector) const;

    double get_intersection_distance (const Ray& ray) const override;


    Vector3 get_normal_at (const Vector3& position) const override;

    Vector3 get_uv_at (const Vector3& position) const override;

    const Vector3& getNormal () const;

    double getIntersect () const;
};



