//
// Created by kaappo on 11.9.2021.
//

#pragma once

#include <optional>
#include <ostream>

#include <glm/glm.hpp>
#include "Plane.h"
#include "Surface.h"

class Triangle : public Surface {
private:
    glm::vec3 t1, t2, t3;
    glm::vec3 tu, tv, tw;

    float d00;
    float d01;
    float d11;
    float invDenom;

    glm::vec3 v0, v1;

    Plane plane;

    bool includes (const glm::vec3& vector) const;
    bool check_bounds (const glm::vec3& P) const;
public:
    Triangle (const glm::vec3& t1, const glm::vec3& t2, const glm::vec3& t3, Material material, const glm::vec3& texture1, const glm::vec3& texture2, const glm::vec3& texture3);
    Triangle (const glm::vec3& t1, const glm::vec3& t2, const glm::vec3& t3, Material material);
    bool getIntersectionDistance (const Ray& ray, Intersection& out) const override;

    glm::vec3 getNormalAt (const glm::vec3& position) const override;
    glm::vec3 getUVAt (const glm::vec3& P) const override;

    AABB getBoundingBox () const override;

    const Material* getMaterial () const override;

    friend std::ostream& operator<< (std::ostream& os, const Triangle& triangle);

    std::ostream& print (std::ostream& os) const override;

    glm::vec3 refract (const glm::vec3& position, const glm::vec3& direction, std::stack<float>& opticalDensities) const override;

};


//extern const float PRECISION_LIMIT = 0.001;
//
//int main () {
//    Triangle triangle = {glm::vec3{-5, 6, 5}, {0, 0, 3}, {5, 6, 3}};
//    std::cout << triangle.getUVAt({4.01, 5.46, 3.11}) << std::endl;
//    std::cout << triangle.getUVAt({-1.95, 2.72, 3.84}) << std::endl;
////    std::cout << "done" << std::endl;
//}
