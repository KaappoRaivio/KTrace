//
// Created by kaappo on 14.9.2021.
//

#pragma once


#include <stack>
#include "Surface.h"

class Sphere : public Surface {
private:
    glm::vec3 center;
    float radius;
    Material* material;

    bool includes (const glm::vec3& point) const;

public:
    Sphere (glm::vec3 center, float radius, Material* material);

    bool getIntersectionDistance (const Ray& ray, Intersection& out) const override;

    glm::vec3 getNormalAt (const glm::vec3& position) const override;
    glm::vec3 getUVAt (const glm::vec3& position) const override;

    AABB getBoundingBox () const override;

    const Material* getMaterial () const override;

    glm::vec3 refract (const glm::vec3& position, const glm::vec3& direction, std::stack<float>& opticalDensities) const override;
};



