//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <optional>
#include "../common/MyVector3.h"
#include "Ray.h"
#include "Surface.h"
#include "../engine/Material.h"

class Plane : public Surface {
private:
    MyVector3 normal;
    double intersect;

    const Material* material;
public:
    Plane (MyVector3 normal, double intersect, const Material* material);

    static Plane from_three_points (const MyVector3& t1, const MyVector3& t2, const MyVector3& t3, const Material* material);

    bool includes (const MyVector3& vector) const;

    double getIntersectionDistance (const Ray& ray, Surface*& hitSurface, const Material*& hitMaterial) override;


    MyVector3 getNormalAt (const MyVector3& position) const override;
    MyVector3 getUVAt (const MyVector3& position) const override;

    AABB getBoundingBox () const override;

    const MyVector3& getNormal () const;

    double getIntersect () const;

    const Material* getMaterial () const override;
};



