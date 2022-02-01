//
// Created by kaappo on 14.9.2021.
//

#pragma once


#include "Surface.h"

class Sphere : public Surface {
private:
    MyVector3 center;
    double radius;
    const Material* material;

    bool includes (const MyVector3& point) const;

public:
    Sphere (MyVector3 center, double radius, const Material* material);

    double getIntersectionDistance (const Ray& ray, const Surface*& hitSurface, const Material*& hitMaterial) const override;

    MyVector3 getNormalAt (const MyVector3& position) const override;
    MyVector3 getUVAt (const MyVector3& position) const override;

    AABB getBoundingBox () const override;

    const Material* getMaterial () const override;
};



