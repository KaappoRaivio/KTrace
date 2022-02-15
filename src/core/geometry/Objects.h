//
// Created by kaappo on 28.1.2022.
//

#pragma once


#include "Surface.h"
#include "../engine/Material.h"

class Objects : public Surface {
private:
    std::vector<std::unique_ptr<Surface>> surfaces;
public:
    Objects (std::vector<std::unique_ptr<Surface>> surfaces);

public:
//    MyVector3 getBumpAt (const MyVector3& position) const override;
//    MyVector3 getUVAt (const MyVector3& position) const override;
    MyVector3 getNormalAt (const MyVector3& position) const override;

    MyVector3 getUVAt (const MyVector3& position) const override;

    const Material* getMaterial () const override;

    double getIntersectionDistance (const Ray& ray, const Surface*& hitSurface, const Material*& hitMaterial) const override;
//    std::optional<Intersection> get_intersection (const Ray& ray) const override;
    AABB getBoundingBox () const override;

//    double getIntersectionDistance (const Ray& ray, const Surface* hitSurface) const override;

//    AABB getBoundingBox () const override;
};



