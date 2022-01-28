//
// Created by kaappo on 28.1.2022.
//

#include "BVH.h"
#include "../common/mytypes.h"

int prunes = 0;

double BVHNode::getIntersectionDistance (const Ray& ray, Surface*& hitSurface, Material& hitMaterial) {
    if (std::abs(box.getIntersectionDistance(ray)) < PRECISION_LIMIT) {
        prunes++;
        std::cout << "Pruned!" << prunes << std::endl;
        return false;
    }


    Surface* leftTempHitSurface = nullptr;
    Material leftTempHitMaterial = Materials::WHITE;
    double leftDistance = left->getIntersectionDistance(ray, leftTempHitSurface, leftTempHitMaterial);

    Surface* rightTempHitSurface = nullptr;
    Material rightTempHitMaterial = Materials::WHITE;
    double rightDistance = right->getIntersectionDistance(ray, rightTempHitSurface, rightTempHitMaterial);
//    std::cout << leftDistance << std::endl;


    if (std::abs(rightDistance) > PRECISION_LIMIT) {
        if (std::abs(leftDistance) > PRECISION_LIMIT) {
            if (rightDistance <= leftDistance) {
                hitSurface = rightTempHitSurface;
                hitMaterial = rightTempHitMaterial;
                return rightDistance;
            } else {
                hitSurface = leftTempHitSurface;
                hitMaterial = leftTempHitMaterial;
                return leftDistance;
            }
        } else {
            hitSurface = rightTempHitSurface;
            hitMaterial = rightTempHitMaterial;
            return rightDistance;
        }
    } else if (std::abs(leftDistance) > PRECISION_LIMIT) {
        hitSurface = leftTempHitSurface;
        hitMaterial = leftTempHitMaterial;
        return leftDistance;
    } else {
        return 0;
    }


//    if (std::abs(rightDistance) > PRECISION_LIMIT && rightDistance <= leftDistance) {
//        hitSurface = rightTempHitSurface;
//        hitMaterial = rightTempHitMaterial;
//        return rightDistance;
//    } else {
//        std::cout << rightDistance << ", " << leftDistance << std::endl;
//
//    }
//
//    if (std::abs(leftDistance) > PRECISION_LIMIT && leftDistance <= rightDistance) {
//        hitSurface = leftTempHitSurface;
//        hitMaterial = leftTempHitMaterial;
//        return leftDistance;
//    }

//    std::cout << "Falling through!" << rightDistance << ", " << leftDistance << ", " << std::endl;
    return 0;
//    if (leftDistance) return leftDistance;
//    else if (rightDistance) return rightDistance;
//    else return 0;
}

bool boxCompare (const std::shared_ptr<Surface> a, const std::shared_ptr<Surface> b, int axis) {


    return a->getBoundingBox().getMinimum()[axis] < b->getBoundingBox().getMinimum()[axis];
//    if (!a->bounding_box(0,0, box_a) || !b->bounding_box(0,0, box_b))
//        std::cerr << "No bounding box in bvh_node constructor.\n";
//
//    return box_a.min().e[axis] < box_b.min().e[axis];
}


bool boxCompareX (const std::shared_ptr<Surface> a, const std::shared_ptr<Surface> b) {
    return boxCompare(a, b, 0);
}

bool boxCompareY (const std::shared_ptr<Surface> a, const std::shared_ptr<Surface> b) {
    return boxCompare(a, b, 1);
}

bool boxCompareZ (const std::shared_ptr<Surface> a, const std::shared_ptr<Surface> b) {
    return boxCompare(a, b, 2);
}

BVHNode::BVHNode (std::vector<std::shared_ptr<Surface>> surfaces) : BVHNode{surfaces, 0, 0, surfaces.size()} {
}

BVHNode::BVHNode (std::vector<std::shared_ptr<Surface>>& src_surfaces, int axis, size_t start, size_t end) : box{true}, left{}, right{} {
    auto comparator = (axis == 0) ?
                      boxCompareX : (axis == 1) ?
                                    boxCompareY : boxCompareZ;

    std::vector<std::shared_ptr<Surface>> surfaces = src_surfaces;


    size_t objectSpan = end - start;
    if (objectSpan == 1) {
        left = surfaces[start];
        right = surfaces[start];
    } else if (objectSpan == 2) {
        if (comparator(surfaces[start], surfaces[start + 1])) {
            left = surfaces[start];
            right = surfaces[start + 1];
        } else {
            left = surfaces[start + 1];
            right = surfaces[start];
        }
    } else {
        std::sort(surfaces.begin() + start, surfaces.begin() + end, comparator);
        size_t mid = start + objectSpan / 2;

        left = make_shared<BVHNode>(surfaces, (axis + 1) % 3, start, mid);
        right = make_shared<BVHNode>(surfaces, (axis + 1) % 3, mid, end);
    }

    AABB leftBB = left->getBoundingBox();
    AABB rightBB = right->getBoundingBox();

    if (leftBB == AABBs::INVALID || rightBB == AABBs::INVALID) {
        throw std::runtime_error("All objects must have a valid bounding box");
    }

    box = leftBB.expand(rightBB);
}

AABB BVHNode::getBoundingBox () const {
    return box;
}

MyVector3 BVHNode::getNormalAt (const MyVector3& position) const {
    throw std::runtime_error("getNormalAt not implemented for BVHNode!");
}

MyVector3 BVHNode::getUVAt (const MyVector3& position) const {
    throw std::runtime_error("getUVAt not implemented for BVHNode!");
    throw std::runtime_error("getUVAt not implemented for BVHNode!");
}

const Material* BVHNode::getMaterial () const {
    throw std::runtime_error("getMaterial not implemented for BVHNode!");
}


