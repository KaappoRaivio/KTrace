//
// Created by kaappo on 11.9.2021.
//
#include <random>
#include <cmath>
#include <chrono>
#include <cstdlib>
#include <glm/gtx/string_cast.hpp>

#include "MyVector3.h"



//glm::vec3 glm::vec3::operator+ (const glm::vec3& other) const {
//    return {vector + other.vector};
//}
//
//std::ostream& operator<< (std::ostream& os, const glm::vec3& vector3) {
//    os << "(" << vector3.vector.x << ", " << vector3.vector.y << ", " << vector3.vector.z << ")";
//    return os;
//}
//
//glm::vec3 glm::vec3::operator- () const {
//    return {-vector};
//}
//
//glm::vec3 glm::vec3::operator- (const glm::vec3& other) const {
//    return *this + -other;
//}
//
//glm::vec3 glm::vec3::operator* (float other) const {
//    return {vector * other};
//}
//
//glm::vec3 glm::vec3::operator/ (float other) const {
//    return {vector / other};
//}
//
//
//float glm::vec3::operator* (const glm::vec3& other) const {
//    return glm::dot(vector, other.vector);
//}
//
//glm::vec3 glm::vec3::cross (const glm::vec3& other) const {
//    return glm::cross(vector, other.vector);
//}
//
//float glm::vec3::length () const {
//    return glm::length(vector);
//}
//
//float glm::vec3::squared () const {
//    return glm::dot(vector, vector);
//}
//
//glm::vec3 glm::vec3::normalize () const {
//    return glm::normalize(vector);
//}
//
//glm::vec3 glm::vec3::rotate (float yaw, float pitch) const {
//    return {vector.x * cos(yaw) + (vector.z * sin(pitch) + vector.y * cos(pitch)) * sin(yaw), -vector.x * sin(yaw) + (vector.z * sin(pitch) + vector.y * cos(pitch)) * cos(yaw), vector.z * cos(pitch) - vector.y * sin(pitch)};
//}
//
//glm::vec3 glm::vec3::reflection (const glm::vec3& axis) const {
//
//    return glm::reflect(vector, axis.vector);
//
////    return *this - axis * (2 * (*this * axis) / squared());
//}
//
//glm::vec3 glm::vec3::randomInsideUnitSphere () {
//    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
//    std::default_random_engine generator{seed};
//
//    std::normal_distribution<float> d(0, 1);
//
//    float i = d(generator);
//    float j = d(generator);
//    float k = d(generator);
//
//
//    const glm::vec3& normalized = glm::vec3(i, j, k).normalize();
//
//
//    std::uniform_real_distribution<float> dist(0, 1);
//
//    float radius = std::pow(dist(generator), 1.0 / 3.0);
//    return normalized * radius;
//}
//
//glm::vec3 glm::vec3::inTermsOfComponents (const glm::vec3& i, const glm::vec3& j, const glm::vec3& k) const {
//    Eigen::Matrix3d A;
//    A << i.vector.x, i.vector.y, i.vector.z, j.vector.x, j.vector.y, j.vector.z, k.vector.x, k.vector.y, k.vector.z;
//    A.transposeInPlace();
//
//    Eigen::Vector3d b;
//    b << vector.x, vector.y, vector.z;
//    Eigen::Vector3d x = A.colPivHouseholderQr().solve(b);
//
//    return {x[0], x[1], x[2]};
//}
//

//
//glm::vec3 glm::vec3::rotateInsideCone (float radius) const {
//    if (radius == 0) {
//        return *this;
//    }
//
//    const glm::vec3& tangent = cross(glm::vec3s::UP).normalize();
//    const glm::vec3& bitangent = cross(tangent).normalize();
//
//    float scatterRadius = std::pow(angleDistribution(generator), 1 / 2.0) * radius;
//
//    float angle = angleDistribution(generator);
//    float x = std::cos(angle) * scatterRadius;
//    float y = std::sin(angle) * scatterRadius;
//
//
//    return tangent * x + bitangent * y + *this;
//
//}
//
//glm::vec3::operator bool () const {
//    return squared() != 0;
//}
//
//glm::vec3 glm::vec3::operator|| (const glm::vec3& other) const {
//    return bool(*this) ? *this : other;
//}
//
//float glm::vec3::atan2 () const {
//    return std::atan2(vector.y, vector.x);
//}
//
//float glm::vec3::asin () const {
//    return std::asin(vector.z);
//}
//
//
//float glm::vec3::getI () const {
//    return vector.x;
//}
//
//float glm::vec3::getJ () const {
//    return vector.y;
//}
//
//float glm::vec3::getK () const {
//    return vector.z;
//}
//
//float glm::vec3::dot (const glm::vec3& other) const {
////    return 0;
////    return i * other.vector.x + j * other.j + k * other.k;
//    return glm::dot(vector, other.vector);
//}
//
//float glm::vec3::operator[] (int index) const {
//    return vector[index];
////    switch (index) {
////        case 0:
////            return i;
////        case 1:
////            return j;
////        case 2:
////            return k;
////        default:
////            std::stringstream ss;
////            ss << "Invalid dimension " << index << "!";
////            throw std::runtime_error(ss.str());
////    }
//}
//
//bool glm::vec3::operator== (const glm::vec3& rhs) const {
//    return vector == rhs.vector;
////    return i == rhs.i &&
////           j == rhs.j &&
////           k == rhs.k;
//}
//
//bool glm::vec3::operator!= (const glm::vec3& rhs) const {
//    return !(rhs == *this);
//}

//int main () {
//    std::cout << "Hello, world" << std::endl;
//
//    glm::vec3 a = {0, 0, 1};
//
//    glm::vec3 i = {1, 0, 0};
//    glm::vec3 j = {1, 1, 0};
//    glm::vec3 k = {1, 0, 1};
//
//    std::cout << a.inTermsOfComponents(i, j, k) << std::endl;
//}
glm::vec3 VectorOperations::changeComponents (const glm::vec3& B, const glm::vec3& newX, const glm::vec3& newY, const glm::vec3& newZ) {
    glm::mat3x3 A{newX.x, newX.y, newX.z, newY.x, newY.y, newY.z, newZ.x, newZ.y, newZ.z};
    A = glm::transpose(A);

//    std::cout << glm::to_string(A) << std::endl;
//    std::cout << glm::to_string(glm::inverse(A)) << std::endl;
    return glm::inverse(A) * B;

//    Eigen::Matrix3d A;
//    A << newX.x, newX.y, newX.z, newY.x, newY.y, newY.z, newZ.x, newZ.y, newZ.z;
//    A.transposeInPlace();
//
//    Eigen::Vector3d b;
//    b << B.x, B.y, B.z;
//    Eigen::Vector3d x = A.colPivHouseholderQr().solve(b);
//
//    return {x[0], x[1], x[2]};
}

//glm::vec3 VectorOperations::randomInsideUnitSphere()
const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine generator{seed};

std::normal_distribution<float> normalDistribution(0, 1);
std::uniform_real_distribution<float> uniformRealDistribution(0, 1);
std::uniform_real_distribution<float> angleDistribution(0, 2 * M_PI);

glm::vec3 VectorOperations::rotateInsideCone (const glm::vec3& vector, float radius) {
    if (radius == 0) {
        return vector;
    }

    const glm::vec3& tangent = glm::normalize(glm::cross(vector, {0, 0, 1}));
    const glm::vec3& bitangent = glm::normalize(glm::cross(vector, tangent));

    float scatterRadius = std::pow(angleDistribution(generator), 1 / 2.0) * radius;

    float angle = angleDistribution(generator);
    float x = std::cos(angle) * scatterRadius;
    float y = std::sin(angle) * scatterRadius;


    return tangent * x + bitangent * y + vector;
}

glm::vec3 VectorOperations::rotate (const glm::vec3 vector, float yaw, float pitch) {
    return {vector.x * cos(yaw) + (vector.z * sin(pitch) + vector.y * cos(pitch)) * sin(yaw), -vector.x * sin(yaw) + (vector.z * sin(pitch) + vector.y * cos(pitch)) * cos(yaw), vector.z * cos(pitch) - vector.y * sin(pitch)};
}