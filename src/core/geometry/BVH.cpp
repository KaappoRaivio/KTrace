//
// Created by kaappo on 28.1.2022.
//

#include <stack>
#include <sstream>
#include "BVH.h"
#include "../common/mytypes.h"

int prunes = 0;

//#define BVHSTACKSIZE 32

bool BVHNode::getIntersectionDistance (const Ray& ray, Intersection& out) const {
    std::stack<const BVHNode*> to_intersect;
//    to_intersect[head++] = this;
    to_intersect.push(this);

    double smallestDistance = 1e9;
    Intersection tempIntersection;

    while (not to_intersect.empty()) {
        const BVHNode* current = to_intersect.top();
        to_intersect.pop();

        if (current->isLeaf()) {
            bool hit = current->payload->getIntersectionDistance(ray, tempIntersection);
            if (hit) {
                float candidate = tempIntersection.distance;
                if (candidate < smallestDistance) {
                    out = tempIntersection;
                    smallestDistance = candidate;
                }
            }
        } else {
            double t_left = std::max(current->left->getBoundingBox().getIntersectionDistance(ray), 0.0);
            double t_right = std::max(current->right->getBoundingBox().getIntersectionDistance(ray), 0.0);

            if (t_left and t_right) {
                if (t_left < t_right) {
                    to_intersect.push(current->right.get());
                    to_intersect.push(current->left.get());
                } else {
                    to_intersect.push(current->left.get());
                    to_intersect.push(current->right.get());
                }
            } else {
                if (t_left) to_intersect.push(current->left.get());
                if (t_right) to_intersect.push(current->right.get());
            }
        }
    }
//    std::cout << "smallest distance: " << smallestDistance << std::endl;
    if (smallestDistance != 1e9) {
//        out = tempIntersection;
        return true;
    } else {
        return false;
    }
//    return smallestDistance != 1e9;
}

std::ostream& operator<< (std::ostream& os, const BVHNode& node) {
    std::stringstream tab;
    for (int i = 0 ; i < node.depth ; ++i) tab << "\t";
    if (node.isLeaf()) {
        os << tab.str() << node.payload->getBoundingBox();
        return os;
    }

    os << tab.str() << "BHV (" << node.box << ") {" << std::endl;
    if (BVHNode* lleft = dynamic_cast<BVHNode*>(node.left.get())) {
        os << *lleft << std::endl;
    } else {
        os << tab.str() << "\t" << node.left->getBoundingBox() << std::endl;
    }

    if (BVHNode* rright = dynamic_cast<BVHNode*>(node.right.get())) {
        os << *rright << std::endl;
    } else {
        os << tab.str() << "\t" << node.right->getBoundingBox() << std::endl;
    }

    os << tab.str() << "}";
    return os;
}

bool BVH::getIntersectionDistance (const Ray& ray, Intersection& out) const {
    return root->getIntersectionDistance(ray, out);
}

AABB BVH::getBoundingBox () const {
    return root->getBoundingBox();
}

glm::vec3 BVH::getNormalAt (const glm::vec3& position) const {
    return root->getNormalAt(position);
}

glm::vec3 BVH::getUVAt (const glm::vec3& position) const {
    return root->getUVAt(position);
}

const Material* BVH::getMaterial () const {
    return root->getMaterial();
}

BVH::BVH (std::vector<std::unique_ptr<Surface>> objects) : objects{std::move(objects)} {
    std::vector<Surface*> rawPointers;
    rawPointers.reserve(this->objects.size());
    for (const auto& object : this->objects) {
        rawPointers.push_back(object.get());
    }

    std::cout << "Creating BVH with " << rawPointers.size() << " polygons " << std::endl;
    root = std::make_unique<BVHNode>(rawPointers);
    std::cout << "Created BVH" << std::endl;
}

std::ostream& BVH::print (std::ostream& os) const {
//    os << "paska" << std::endl;
    os << *root;
    return os;
}

bool boxCompare (const Surface* const a, const Surface* const b, int axis) {


    return a->getBoundingBox().getMinimum()[axis] < b->getBoundingBox().getMinimum()[axis];
//    if (!a->bounding_box(0,0, box_a) || !b->bounding_box(0,0, box_b))
//        std::cerr << "No bounding box in bvh_node constructor.\n";
//
//    return box_a.min().e[depth] < box_b.min().e[depth];
}


bool boxCompareX (const Surface* a, const Surface* b) {
    return boxCompare(a, b, 0);
}

bool boxCompareY (const Surface* a, const Surface* b) {
    return boxCompare(a, b, 1);
}

bool boxCompareZ (const Surface* a, const Surface* b) {
    return boxCompare(a, b, 2);
}

BVHNode::BVHNode (std::vector<Surface*> surfaces) : BVHNode{surfaces, 0, 0, surfaces.size()} {
}

BVHNode::BVHNode (std::vector<Surface*> src_surfaces, int axis, size_t start, size_t end) : box{true}, left{}, right{}, depth{axis} {
    auto comparator = (axis % 3 == 0) ? boxCompareX
                                      : ((axis % 3 == 1) ? boxCompareY
                                                         : boxCompareZ);


//    std::vector<std::shared_ptr<Surface>> surfaces = src_surfaces;


    size_t objectSpan = end - start;
    if (objectSpan == 0) throw std::runtime_error("A BVH hierarchy cannot be empty!");
    if (objectSpan == 1) {
        payload = src_surfaces[start];
        box = payload->getBoundingBox();
    } else {

        std::sort(src_surfaces.begin() + start, src_surfaces.begin() + end, comparator);
        size_t mid = start + objectSpan / 2;
//        std::nth_element(src_surfaces.begin() + start, src_surfaces.begin() + mid, src_surfaces.begin() + end, comparator);

        left = make_unique<BVHNode>(src_surfaces, axis + 1, start, mid);
        right = make_unique<BVHNode>(src_surfaces, axis + 1, mid, end);

        AABB leftBB = left->getBoundingBox();
        AABB rightBB = right->getBoundingBox();

        if (leftBB == AABBs::INVALID || rightBB == AABBs::INVALID) {
            throw std::runtime_error("All objects must have a valid bounding box");
        }

        box = leftBB.expand(rightBB);
    }

}

AABB BVHNode::getBoundingBox () const {
    return box;
}

glm::vec3 BVHNode::getNormalAt (const glm::vec3& position) const {
    throw std::runtime_error("getBumpAt not implemented for BVHNode!");
}

glm::vec3 BVHNode::getUVAt (const glm::vec3& position) const {
    throw std::runtime_error("getUVAt not implemented for BVHNode!");
}

const Material* BVHNode::getMaterial () const {
    throw std::runtime_error("getMaterial not implemented for BVHNode!");
}

BVHNode::BVHNode () : box{AABBs::INVALID} {

}

bool BVHNode::isLeaf () const {
    return payload != nullptr;
}


