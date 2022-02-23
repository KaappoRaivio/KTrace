//
// Created by kaappo on 11.9.2021.
//

#pragma once

#include <optional>
#include <ostream>
#include <stack>

#include "Ray.h"
#include "AABB.h"
#include "Hittable.h"
#include "../common/Intersection.h"


class Surface : public Hittable {
public:

    virtual glm::vec3 getUVAt (const glm::vec3& position) const = 0;
    virtual glm::vec3 refract (const glm::vec3& position, const glm::vec3& direction, std::stack<float>& opticalDensities) const;
    virtual glm::vec3 getNormalAt (const glm::vec3& position) const = 0;
    virtual AABB getBoundingBox () const = 0;

    virtual const Material* getMaterial () const = 0;

    virtual std::ostream& print (std::ostream& os) const;

    bool getIntersection (const Ray& ray, Intersection& out);

    glm::vec3 getBumpedNormalAt (const glm::vec3& position) const;
    friend std::ostream& operator<< (std::ostream& os, const Surface& surface);

};



