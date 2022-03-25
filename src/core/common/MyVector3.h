//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <ostream>
#include <iostream>
#include "../../../lib/Eigen/Dense"
#include <glm/glm.hpp>
#include <stack>

namespace VectorOperations {
    glm::vec3 changeComponents (const glm::vec3& B, const glm::vec3& newX, const glm::vec3& newY, const glm::vec3& newZ);

    glm::vec3 rotateInsideCone (const glm::vec3& vector, float radius);

    glm::vec3 rotate (const glm::vec3 vector, float yaw, float pitch);

    glm::vec3 refract (const glm::vec3& direction, glm::vec3 normal, float eta);
}

//class glm::vec3 {
//private:
////    float i, j, k;
//    glm::vec3 vector;
//
//public:
////    constexpr glm::vec3 (float i, float j, float k) : vector{i, j, k} {};
//    constexpr glm::vec3 (double i, double j, double k) : vector{i, j, k} {}
//    constexpr glm::vec3 (const glm::vec3& vector) : vector{vector} {}
//
//    glm::vec3 operator+ (const glm::vec3& other) const;
//    glm::vec3 operator|| (const glm::vec3& other) const;
//    glm::vec3 operator- () const;
//    glm::vec3 operator- (const glm::vec3& other) const;
//    glm::vec3 operator* (float other) const;
//    float operator* (const glm::vec3& other) const;
//    glm::vec3 operator/ (float other) const;
//    explicit operator bool () const;
//    float operator [] (int index) const;
//
//    bool operator== (const glm::vec3& rhs) const;
//
//    bool operator!= (const glm::vec3& rhs) const;
//
//    glm::vec3 rotateInsideCone (float radius) const;
//    glm::vec3 reflection (const glm::vec3& axis) const;
//    glm::vec3 inTermsOfComponents (const glm::vec3& i, const glm::vec3& j, const glm::vec3& k) const;
//
//    glm::vec3 rotate (float yaw, float pitch) const;
//    glm::vec3 cross (const glm::vec3& other) const;
//    float length () const;
//
//    float squared () const;
//    glm::vec3 normalize () const;
//
//    float atan2 () const;
//
//    float asin () const;
//
//    friend std::ostream& operator<< (std::ostream& os, const glm::vec3& vector3);
//
//    float getI () const;
//    float getJ () const;
//    float getK () const;
//
//    static glm::vec3 randomInsideUnitSphere ();
//
//
//    float dot (const glm::vec3& vector3) const;
//};
//
//namespace glm::vec3s {
//    constexpr glm::vec3 UP{0, 0, 1};
//    constexpr glm::vec3 OUT{0, 1, 0};
//    constexpr glm::vec3 SIDE{1, 0, 0};
//}