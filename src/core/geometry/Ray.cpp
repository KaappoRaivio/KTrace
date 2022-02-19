//
// Created by kaappo on 11.9.2021.
//

#include <glm/gtx/string_cast.hpp>
#include "Ray.h"

Ray::Ray (const glm::vec3& origin, const glm::vec3& direction) : origin(origin), direction(glm::normalize(direction)), inverse_direction{1.0 / glm::normalize(direction).x, 1.0 / glm::normalize(direction).y, 1.0 / glm::normalize(direction).z} {}

const glm::vec3& Ray::getOrigin () const {
    return origin;
}

const glm::vec3& Ray::getDirection () const {
    return direction;
}

glm::vec3 Ray::apply (float lambda) const {
    return origin + direction * lambda;
}

std::ostream& operator<< (std::ostream& os, const Ray& ray) {
    os << "origin: " << glm::to_string(ray.origin) << " direction: " << glm::to_string(ray.direction);
    return os;
}

const glm::vec3& Ray::getInverseDirection () const {
    return inverse_direction;
}
