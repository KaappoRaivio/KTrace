//
// Created by kaappo on 11.9.2021.
//

#include "Camera.h"

#include <utility>

Camera::Camera (Vector3 origin, std::pair<double, double> rotation, double viewplane_distance, std::pair<double, double> viewplane_size, std::pair<int, int> viewport_size) : origin{origin}, rotation{std::move(rotation)}, viewplane_distance{viewplane_distance},
                                                                                                                                                                              viewplane_size{std::move(viewplane_size)}, viewport_size{std::move(viewport_size)},
                                                                                                                                                                              direction{Camera::DIRECTION_REFERENCE.rotate(rotation.first, rotation.second)} {}

std::vector<std::vector<Vector3>> Camera::get_viewplane (const int antialiasingScaler) const {
    int viewport_size_x_with_antialiasing = viewport_size.first * antialiasingScaler;
    int viewport_size_y_with_antialiasing = viewport_size.second * antialiasingScaler;

    std::cout << "Generating viewplane with dimensions (" << viewport_size_x_with_antialiasing << ", " << viewport_size_y_with_antialiasing << ")!" << std::endl;


    auto viewport_to_viewplane_x = viewplane_size.first / viewport_size_x_with_antialiasing;
    auto viewport_to_viewplane_z = viewplane_size.second / viewport_size_y_with_antialiasing;


    std::vector<std::vector<Vector3>> viewplane_matrix;
    viewplane_matrix.reserve(viewport_size_y_with_antialiasing);

    for (int z = viewport_size_y_with_antialiasing; z > 0; --z) {
        std::vector<Vector3> viewplane_matrix_row;
        viewplane_matrix_row.reserve(viewport_size_x_with_antialiasing);

        for (int x = 0; x < viewport_size_x_with_antialiasing; ++x) {
            viewplane_matrix_row.push_back(Vector3{viewport_to_viewplane_x * x - viewplane_size.first / 2, viewplane_distance, viewport_to_viewplane_z * z - viewplane_size.second / 2}.rotate(rotation.first, rotation.second).normalize());
        }
        viewplane_matrix.push_back(viewplane_matrix_row);
    }

    return viewplane_matrix;
}

const Vector3& Camera::getOrigin () const {
    return origin;
}
