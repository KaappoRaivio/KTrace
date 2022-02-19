//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <ostream>
#include <glm/glm.hpp>

class Ray {
public:
    Ray (const glm::vec3& origin, const glm::vec3& direction);

private:
    glm::vec3 origin;
    glm::vec3 direction;
    glm::vec3 inverse_direction;
public:
    const glm::vec3& getInverseDirection () const;

public:
    const glm::vec3& getOrigin () const;

    const glm::vec3& getDirection () const;

    glm::vec3 apply (float lambda) const;

    friend std::ostream& operator<< (std::ostream& os, const Ray& ray);
};



