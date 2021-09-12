//
// Created by kaappo on 11.9.2021.
//

#pragma once


#include <array>
#include <vector>
#include "Vector3.h"

class Camera {
private:
    inline static const Vector3 DIRECTION_REFERENCE = {0, 1, 0};

    Vector3 origin;

    double viewplane_distance;
    std::pair<double, double> viewplane_size;
    std::pair<int, int> viewport_size;

    Vector3 direction;
    std::pair<double, double> rotation;

public:
    Camera (Vector3 origin, std::pair<double, double> rotation, double viewplane_distance=2, std::pair<double, double> viewplane_size={1, 1}, std::pair<int, int> viewport_size={80, 80});
    [[nodiscard]] std::vector<std::vector<Vector3>> get_viewplane () const;

    const Vector3 &getOrigin() const;
};



