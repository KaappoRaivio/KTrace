//
// Created by kaappo on 28.1.2022.
//

#pragma once


#include <vector>
#include "Surface.h"
#include "../engine/Material.h"

class Objects : public Surface {
private:
    std::vector<std::unique_ptr<Surface>> surfaces;
public:
    Objects (std::vector<std::unique_ptr<Surface>> surfaces);

public:
//    glm::vec3 getBumpAt (const glm::vec3& position) const override;
//    glm::vec3 getUVAt (const glm::vec3& position) const override;
    glm::vec3 getNormalAt (const glm::vec3& position) const override;

    glm::vec3 getUVAt (const glm::vec3& position) const override;

    const Material* getMaterial () const override;

    bool getIntersectionDistance (const Ray& ray, Intersection& out) const override;
//    std::optional<Intersection> get_intersection (const Ray& ray) const override;
    AABB getBoundingBox () const override;

//    double getIntersectionDistance (const Ray& ray, const Surface* hitSurface) const override;

//    AABB getBoundingBox () const override;
};



