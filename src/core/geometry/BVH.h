//
// Created by kaappo on 28.1.2022.
//

#pragma once


#include "Surface.h"
#include "AABB.h"

class BVHNode : public Surface {
public:
    BVHNode (std::vector<std::shared_ptr<Surface>> surfaces);
    BVHNode (std::vector<std::shared_ptr<Surface>>& src_surfaces, int axis, size_t start, size_t end);

    double getIntersectionDistance (const Ray& ray, Surface*& hitSurface, Material& hitMaterial) override;

    AABB getBoundingBox () const override;

    MyVector3 getNormalAt (const MyVector3& position) const override;

    MyVector3 getUVAt (const MyVector3& position) const override;

    const Material* getMaterial () const override;

private:
    AABB box;
    std::shared_ptr<Surface> left;
    std::shared_ptr<Surface> right;
};



