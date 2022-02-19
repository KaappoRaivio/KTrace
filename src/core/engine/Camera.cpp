//
// Created by kaappo on 11.9.2021.
//

#include "Camera.h"

#include <utility>
#include <glm/gtx/rotate_vector.hpp>
#include <iostream>
#include <glm/gtx/string_cast.hpp>

Camera::Camera (glm::vec3 origin, glm::vec3 lookingAt, float viewplane_distance, std::pair<float, float> viewplane_size, std::pair<int, int> viewport_size) : origin{origin}, viewplane_distance{viewplane_distance},
                                                                                                                                                                 viewplane_size{std::move(viewplane_size)}, viewport_size{std::move(viewport_size)},
                                                                                                                                                                 direction{glm::normalize(lookingAt - origin)} {}

std::vector<std::vector<glm::vec3>> Camera::get_viewplane (const int antialiasingScaler) const {
    int viewport_size_x_with_antialiasing = viewport_size.first * antialiasingScaler;
    int viewport_size_y_with_antialiasing = viewport_size.second * antialiasingScaler;

    std::cout << "Generating viewplane with dimensions (" << viewport_size_x_with_antialiasing << ", " << viewport_size_y_with_antialiasing << ")!" << std::endl;


    auto viewport_to_viewplane_x = viewplane_size.first / viewport_size_x_with_antialiasing;
    auto viewport_to_viewplane_z = viewplane_size.second / viewport_size_y_with_antialiasing;


    std::vector<std::vector<glm::vec3>> viewplane_matrix;
    viewplane_matrix.reserve(viewport_size_y_with_antialiasing);

    auto out = direction;
    auto side = glm::cross(direction, glm::vec3{0, 0, 1});
    auto up = glm::cross(side, out);

    for (int z = viewport_size_y_with_antialiasing; z > 0; --z) {
        std::vector<glm::vec3> viewplane_matrix_row;
        viewplane_matrix_row.reserve(viewport_size_x_with_antialiasing);

        for (int x = 0; x < viewport_size_x_with_antialiasing; ++x) {


//            auto normalize = glm::vec3{viewport_to_viewplane_x * x - viewplane_size.first / 2, viewplane_distance, viewport_to_viewplane_z * z - viewplane_size.second / 2}.rotate(rotation.first, rotation.second).normalize();
            auto d = direction * viewplane_distance + (viewport_to_viewplane_x * x - viewplane_size.first / 2) * side + (viewport_to_viewplane_z * z - viewplane_size.second / 2) * up;
            viewplane_matrix_row.push_back(glm::normalize(d));
        }
        viewplane_matrix.push_back(viewplane_matrix_row);
    }

    return viewplane_matrix;
}

const glm::vec3& Camera::getOrigin () const {
    return origin;
}

std::ostream& operator<< (std::ostream& os, const Camera& camera) {
    return os << "Camera";
}

void Camera::setViewplaneDistance (float viewplaneDistance) {
    this->viewplane_distance = viewplaneDistance;
}

float Camera::getViewplaneDistance () const {
    return viewplane_distance;
}

void Camera::move (const glm::vec3& direction) {
    origin = origin + direction;
}
