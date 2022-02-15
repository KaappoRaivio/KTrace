//
// Created by kaappo on 28.1.2022.
//

#pragma once


#include <ostream>
#include "Surface.h"
#include "AABB.h"
#include "Objects.h"


class BVHNode : public Surface {
public:
    BVHNode ();

    BVHNode (std::vector<Surface*> surfaces);
    BVHNode (std::vector<Surface*> src_surfaces, int axis, size_t start, size_t end);

    double getIntersectionDistance (const Ray& ray, const Surface*& hitSurface, const Material*& hitMaterial) const override;
    AABB getBoundingBox () const override;
    MyVector3 getNormalAt (const MyVector3& position) const override;
    MyVector3 getUVAt (const MyVector3& position) const override;
    const Material* getMaterial () const override;

    bool isLeaf () const;
    friend std::ostream& operator<< (std::ostream& os, const BVHNode& node);
private:
    AABB box;
//    BVHNode left;
//    Objects leafs;
    const Surface* payload = nullptr;
    std::unique_ptr<BVHNode> left;
    std::unique_ptr<BVHNode> right;
    int depth;
};



class BVH : public Surface {
private:
    std::vector<std::unique_ptr<Surface>> objects;
    std::unique_ptr<BVHNode> root{nullptr};
//    std::vector<std::unique_ptr<Surface>> objects;

public:
    BVH (std::vector<std::unique_ptr<Surface>> objects);

    double getIntersectionDistance (const Ray& ray, const Surface*& hitSurface, const Material*& hitMaterial) const override;
    AABB getBoundingBox () const override;
    MyVector3 getNormalAt (const MyVector3& position) const override;
    MyVector3 getUVAt (const MyVector3& position) const override;
    const Material* getMaterial () const override;

    friend std::ostream& operator<< (std::ostream& os, const BVHNode& node);
};
