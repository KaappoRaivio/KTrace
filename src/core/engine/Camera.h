//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <array>
#include <vector>
#include <ostream>
#include <glm/glm.hpp>

class Camera {
private:
    inline static const glm::vec3 DIRECTION_REFERENCE = {0, 1, 0};

    glm::vec3 origin;

    float viewplane_distance;
    std::pair<float, float> viewplane_size;
    std::pair<int, int> viewport_size;

    glm::vec3 direction;

public:
    Camera (glm::vec3 origin, glm::vec3 lookingAt, float viewplane_distance = 2, std::pair<float, float> viewplane_size = {1, 1}, std::pair<int, int> viewport_size = {80, 80});
    std::vector<std::vector<glm::vec3>> get_viewplane (const int i) const;
    const glm::vec3& getOrigin () const;
    friend std::ostream& operator<< (std::ostream& os, const Camera& camera);
    void setViewplaneDistance (float viewplaneDistance);
    float getViewplaneDistance () const;
    void move (const glm::vec3& direction);

};



