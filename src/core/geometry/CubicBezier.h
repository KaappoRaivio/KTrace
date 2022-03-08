//
// Created by kaappo on 5.3.2022.
//

#pragma once


#include <glm/vec3.hpp>
#include <vector>
#include <array>
#include <ostream>
#include "Ray.h"
#include "../common/mytypes.h"


class CubicBezier {
private:
    static constexpr int AMOUNT_OF_SAMPLES = 128;

    glm::vec3 p0, p1, p2, p3;
    std::array<float, AMOUNT_OF_SAMPLES> lengthLUT;
    float k;
public:
    CubicBezier (const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, float k);
    void populateLUT ();

    Ray apply (float t);
    float advance (float oldT, float deltaT);

    friend std::ostream& operator<< (std::ostream& os, const CubicBezier& bezier);

    Ray applyDistance (float d);

    float length () const;
};


class CubicBezierSequence {
    std::vector<CubicBezier> curves;
    std::vector<float> lengths;
public:
    CubicBezierSequence (const std::vector<glm::vec3>& originPoints, const std::vector<glm::vec3>& controlPoints, float k);
    void populateLenghts ();
    Ray apply (float t);

    float advance (float oldT, float deltaT);

    Ray applyDistance (float d);
};