//
// Created by kaappo on 11.9.2021.
//
#include <random>
#include <cmath>
#include <chrono>
#include <cstdlib>

#include "MyVector3.h"



MyVector3 MyVector3::operator+ (const MyVector3& other) const {
    return {vector + other.vector};
}

std::ostream& operator<< (std::ostream& os, const MyVector3& vector3) {
    os << "(" << vector3.vector.x << ", " << vector3.vector.y << ", " << vector3.vector.z << ")";
    return os;
}

MyVector3 MyVector3::operator- () const {
    return {-vector};
}

MyVector3 MyVector3::operator- (const MyVector3& other) const {
    return *this + -other;
}

MyVector3 MyVector3::operator* (float other) const {
    return {vector * other};
}

MyVector3 MyVector3::operator/ (float other) const {
    return {vector / other};
}


float MyVector3::operator* (const MyVector3& other) const {
    return glm::dot(vector, other.vector);
}

MyVector3 MyVector3::cross (const MyVector3& other) const {
    return glm::cross(vector, other.vector);
}

float MyVector3::length () const {
    return glm::length(vector);
}

float MyVector3::squared () const {
    return glm::dot(vector, vector);
}

MyVector3 MyVector3::normalize () const {
    return glm::normalize(vector);
}

MyVector3 MyVector3::rotate (float yaw, float pitch) const {
    return {vector.x * cos(yaw) + (vector.z * sin(pitch) + vector.y * cos(pitch)) * sin(yaw), -vector.x * sin(yaw) + (vector.z * sin(pitch) + vector.y * cos(pitch)) * cos(yaw), vector.z * cos(pitch) - vector.y * sin(pitch)};
}

MyVector3 MyVector3::reflection (const MyVector3& axis) const {
    return *this - axis * (2 * (*this * axis) / squared());
}

MyVector3 MyVector3::randomInsideUnitSphere () {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator{seed};

    std::normal_distribution<float> d(0, 1);

    float i = d(generator);
    float j = d(generator);
    float k = d(generator);


    const MyVector3& normalized = MyVector3(i, j, k).normalize();


    std::uniform_real_distribution<float> dist(0, 1);

    float radius = std::pow(dist(generator), 1.0 / 3.0);
    return normalized * radius;
}

MyVector3 MyVector3::inTermsOfComponents (const MyVector3& i, const MyVector3& j, const MyVector3& k) const {
    Eigen::Matrix3d A;
    A << i.vector.x, i.vector.y, i.vector.z, j.vector.x, j.vector.y, j.vector.z, k.vector.x, k.vector.y, k.vector.z;
    A.transposeInPlace();

    Eigen::Vector3d b;
    b << vector.x, vector.y, vector.z;
    Eigen::Vector3d x = A.colPivHouseholderQr().solve(b);

    return {x[0], x[1], x[2]};
}

MyVector3 MyVector3::rotateInsideCone (float radius) const {
    if (radius == 0) {
        return *this;
    }

    const MyVector3& tangent = cross(MyVector3s::UP).normalize();
    const MyVector3& bitangent = cross(tangent).normalize();

    const unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator{seed};

    std::normal_distribution<float> normalDistribution(0, 1);
    std::uniform_real_distribution<float> uniformRealDistribution(0, 1);
    std::uniform_real_distribution<float> angleDistribution(0, 2 * M_PI);

    float scatterRadius = std::pow(angleDistribution(generator), 1 / 2.0) * radius;

    float angle = angleDistribution(generator);
    float x = std::cos(angle) * scatterRadius;
    float y = std::sin(angle) * scatterRadius;


    return tangent * x + bitangent * y + *this;

}

MyVector3::operator bool () const {
    return squared() != 0;
}

MyVector3 MyVector3::operator|| (const MyVector3& other) const {
    return bool(*this) ? *this : other;
}

float MyVector3::atan2 () const {
    return std::atan2(vector.y, vector.x);
}

float MyVector3::asin () const {
    return std::asin(vector.z);
}


float MyVector3::getI () const {
    return vector.x;
}

float MyVector3::getJ () const {
    return vector.y;
}

float MyVector3::getK () const {
    return vector.z;
}

float MyVector3::dot (const MyVector3& other) const {
//    return 0;
//    return i * other.vector.x + j * other.j + k * other.k;
    return glm::dot(vector, other.vector);
}

float MyVector3::operator[] (int index) const {
    return vector[index];
//    switch (index) {
//        case 0:
//            return i;
//        case 1:
//            return j;
//        case 2:
//            return k;
//        default:
//            std::stringstream ss;
//            ss << "Invalid dimension " << index << "!";
//            throw std::runtime_error(ss.str());
//    }
}

bool MyVector3::operator== (const MyVector3& rhs) const {
    return vector == rhs.vector;
//    return i == rhs.i &&
//           j == rhs.j &&
//           k == rhs.k;
}

bool MyVector3::operator!= (const MyVector3& rhs) const {
    return !(rhs == *this);
}

//int main () {
//    std::cout << "Hello, world" << std::endl;
//
//    MyVector3 a = {0, 0, 1};
//
//    MyVector3 i = {1, 0, 0};
//    MyVector3 j = {1, 1, 0};
//    MyVector3 k = {1, 0, 1};
//
//    std::cout << a.inTermsOfComponents(i, j, k) << std::endl;
//}