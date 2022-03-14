//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <optional>
#include <glm/glm.hpp>
#include "Ray.h"
#include "Surface.h"
#include "../engine/materials/Material.h"

class Plane : public Surface {
private:
    glm::vec3 normal;
    double intersect;

    const Material* material;
public:
    Plane (glm::vec3 normal, double intersect, const Material* material);

    static Plane from_three_points (const glm::vec3& t1, const glm::vec3& t2, const glm::vec3& t3, const Material* material);

    bool includes (const glm::vec3& vector) const;

    bool getIntersectionDistance (const Ray& ray, Intersection& out) const override;


    glm::vec3 getNormalAt (const glm::vec3& position) const override;
    glm::vec3 getUVAt (const glm::vec3& position) const override;

    AABB getBoundingBox () const override;

    const glm::vec3& getNormal () const;

    double getIntersect () const;

    const Material* getMaterial () const override;

    std::ostream& print (std::ostream& os) const override;
};



