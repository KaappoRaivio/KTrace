//
// Created by kaappo on 5.3.2022.
//

#include "CubicBezier.h"

CubicBezier::CubicBezier (const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, float k) : p0{p0}, p1{p1}, p2{p2}, p3{p3}, k{k} {

    populateLUT();
//    this->k = k;
}

void CubicBezier::populateLUT () {
    float step = 1.f / AMOUNT_OF_SAMPLES;

//    std::array<float, AMOUNT_OF_SAMPLES> timeLUT;
    lengthLUT[0] = 0;

    auto previous = apply(0).getOrigin();
    for (float t = step ; t < 1 ; t += step) {
        auto point = apply(t).getOrigin();
        lengthLUT[t * AMOUNT_OF_SAMPLES] = glm::length(previous - point) + lengthLUT[(t - step) * AMOUNT_OF_SAMPLES];
        previous = point;
    }

//    for (int i = 0 ; i < AMOUNT_OF_SAMPLES ; ++i) {
//        std::cout << lengthLUT[i] << ", ";
//    }
//    std::cout << std::endl;
}


Ray CubicBezier::apply (float t) {
    t = std::clamp(t, 0.0f, 1.0f);

    float t0 = -std::pow(t, 3) + 3 * std::pow(t, 2) - 3 * t + 1;
    float t1 = 3 * std::pow(t, 3) - 6 * std::pow(t, 2) + 3 * t;
    float t2 = -3 * std::pow(t, 3) + 3 * std::pow(t, 2);
    float t3 = std::pow(t, 3);

    float Dt0 = -3 * std::pow(t, 2) + 6 * t - 3;
    float Dt1 = 9 * std::pow(t, 2) - 12 * t + 3;
    float Dt2 = -9 * std::pow(t, 2) + 6 * t;
    float Dt3 = 3 * std::pow(t, 2);

    float DDt0 = -6 * t + 6;
    float DDt1 = 18 * t - 12;
    float DDt2 = -18 * t + 6;
    float DDt3 = 6 * t;

    auto position = t0 * p0 + t1 * p1 + t2 * p2 + t3 * p3;
    auto direction = glm::normalize(Dt0 * p0 + Dt1 * p1 + Dt2 * p2 + Dt3 * p3) * k + glm::normalize(DDt0 * p0 + DDt1 * p1 + DDt2 * p2 + DDt3 * p3) * (1 - k);

    return {position, direction};
}

Ray CubicBezier::applyDistance (float d) {
    d = d * length();
    auto index = std::lower_bound(lengthLUT.begin(), lengthLUT.end(), d) - lengthLUT.begin();

    float lowerT = (float) index / AMOUNT_OF_SAMPLES;
    float upperT = (float) (index + 1) / AMOUNT_OF_SAMPLES;


//    std::cout << lowerT << ", " << upperT << std::endl;

    float percentage = (d - lengthLUT[index - 1]) / (lengthLUT[index] - lengthLUT[index - 1]);
//    std::cout << percentage << std::endl;


//    std::cout << lengthLUT[index - 1] << ", " << lengthLUT[index] << std::endl;


    return apply(std::lerp(lowerT, upperT, percentage));
}

float CubicBezier::advance (float oldT, float deltaT) {
    glm::vec3 v0 = -3.f * p0 + 9.f * p1 - 9.f * p2 + 3.f * p3;
    glm::vec3 v1 = 6.f * p0 - 12.f * p1 + 6.f * p2;
    glm::vec3 v2 = -3.f * p0 + 3.f * p1;
//    float Dt0 = -3 * std::pow(oldT, 2) + 6 * oldT - 3;
//    float Dt1 = 9 * std::pow(oldT, 2) - 12 * oldT + 3;
//    float Dt2 = -9 * std::pow(oldT, 2) + 6 * oldT;
//    float Dt3 = 3 * std::pow(oldT, 2);
//    glm::vec3 derivative = Dt0 * p0 + Dt1 * p1 + Dt2 * p2 + Dt3 * p3;

//    std::cout << oldT + deltaT / glm::length(std::pow(oldT, 2.f) * v0 + oldT * v1 + v2) << std::endl;
    return oldT + deltaT / glm::length(std::pow(oldT, 2.f) * v0 + oldT * v1 + v2);
}

float CubicBezier::length () const {
    return lengthLUT[AMOUNT_OF_SAMPLES - 1];
}

std::ostream& operator<< (std::ostream& os, const CubicBezier& bezier) {
    os << "CubicBezier{" << bezier.p0 << ", " << bezier.p1 << ", " << bezier.p2 << ", " << bezier.p3 << "}";
    return os;
}


CubicBezierSequence::CubicBezierSequence (const std::vector<glm::vec3>& originPoints, const std::vector<glm::vec3>& controlPoints, const float k) : curves{} {
    for (int i = 0 ; i < originPoints.size() - 1 ; ++i) {
        curves.push_back({originPoints[i], originPoints[i] + controlPoints[i], originPoints[i + 1] - controlPoints[i + 1], originPoints[i + 1], k});
//        std::cout << curves.back() << std::endl;
//        curves.emplace_back(originPoints[i], originPoints[i] + controlPoints[i], originPoints[i + 1], originPoints[i + 1] + controlPoints[i + 1], k);
    }

    populateLenghts();

//    std::exit(0);
}

void CubicBezierSequence::populateLenghts () {
    lengths.reserve(curves.size());

    float totalLength = 0;
    for (const auto& curve : curves) {
        totalLength += curve.length();
    }

    lengths.push_back(0);
    for (const auto& curve : curves) {
        lengths.push_back(curve.length() / totalLength + lengths.back());
    }
}


Ray CubicBezierSequence::apply (float t) {
    t = std::clamp(t, 0.f, 1.f - std::numeric_limits<float>::epsilon());
    auto step = 1.f / curves.size();
    return curves[static_cast<int>((t - std::numeric_limits<float>::epsilon()) * curves.size())].apply(std::fmod(t, step) / step);
}

float CubicBezierSequence::length () {
    return lengths[AMOUNT_OF_SAMPLES - 1];
}

Ray CubicBezierSequence::applyDistance (float d) {
    auto index = std::lower_bound(lengths.begin(), lengths.end(), d) - lengths.begin();

    float actualLength = lengths[index] - lengths[index - 1];
    return curves[index - 1].applyDistance((d - lengths[index - 1]) / actualLength);
}

float CubicBezierSequence::advance (float oldT, float deltaT) {
    return oldT + deltaT;
//    auto step = 1.f / curves.size();
//    return curves[static_cast<int>((oldT - std::numeric_limits<float>::epsilon()) * curves.size())].advance(std::fmod(oldT, step) / step, deltaT);
}

