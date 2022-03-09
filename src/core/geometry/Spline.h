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


static constexpr int AMOUNT_OF_SAMPLES = 128;

class Spline {
private:

    glm::vec3 p0, p1, p2, p3;
    std::array<float, AMOUNT_OF_SAMPLES> lengthLUT;
    float k{0.9f};
public:
    Spline (const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, float k);
    void populateLUT ();

    glm::vec3 apply (float t) const;
    glm::vec3 applyDistance (float d) const;

    float advance (float oldT, float deltaT);
    float length () const;

    friend std::ostream& operator<< (std::ostream& os, Spline bezier);
};


class SplineSequence {
    std::vector<Spline> curves;
    std::vector<float> lengths;
public:
    SplineSequence (const std::vector<glm::vec3>& points, const float k);
    void populateLenghts ();

    Ray apply (float t, bool compensateDistance) const;

    float advance (float oldT, float deltaT);
    float length ();

    static SplineSequence getRandomSequence (int length, glm::vec3 origin);

    friend std::ostream& operator<< (std::ostream& os, SplineSequence sequence);

    glm::vec3 getPoint (float t, bool compensateDistance) const;

    glm::vec3 getPoint (float t) const;
};