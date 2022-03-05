//
// Created by kaappo on 5.3.2022.
//

#include "CubicBezier.h"

CubicBezier::CubicBezier (const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3) : p0(p0), p1(p1), p2(p2), p3(p3) {}

Ray CubicBezier::apply (double t) {
    t = std::clamp(t, 0.0, 1.0);

    float t0 = -std::pow(t, 3) + 3 * std::pow(t, 2) - 3 * t + 1;
    float t1 = 3 * std::pow(t, 3) - 6 * std::pow(t, 2) + 3 * t;
    float t2 = -3 * std::pow(t, 3) + 3 * std::pow(t, 2);
    float t3 = std::pow(t, 3);

    float Dt0 = -3 * std::pow(t, 2) + 6 * t - 3;
    float Dt1 = 9 * std::pow(t, 2) - 12 * t + 3;
    float Dt2 = -9 * std::pow(t, 3) + 6 * t;
    float Dt3 = 3 * std::pow(t, 2);

    auto position = t0 * p0 + t1 * p1 + t2 * p2 + t3 * p3;
    auto direction = glm::normalize(Dt0 * p0 + Dt1 * p1 + Dt2 * p2 + Dt3 * p3);

    return {position, direction};
}
