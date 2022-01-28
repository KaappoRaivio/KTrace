//
// Created by kaappo on 11.9.2021.
//

#pragma once

#include <optional>
#include <ostream>

#include "Ray.h"
#include "AABB.h"
#include "Hittable.h"
#include "../common/Intersection.h"


class Surface : public Hittable {
public:
    virtual MyVector3 getNormalAt (const MyVector3& position) const = 0;
    virtual MyVector3 getUVAt (const MyVector3& position) const = 0;
    virtual AABB getBoundingBox () const = 0;

    virtual const Material* getMaterial () const = 0;

    std::optional<Intersection> getIntersection (const Ray& ray);

    friend std::ostream& operator<< (std::ostream& os, const Surface& surface);
};



