//
// Created by kaappo on 5.3.2022.
//

#include <chrono>
#include <random>
#include "Spline.h"
#include "../common/MyVector3.h"
#include <glm/gtx/spline.hpp>

Spline::Spline (const glm::vec3& p0, const glm::vec3& p1, const glm::vec3& p2, const glm::vec3& p3, float k) : p0{p0}, p1{p1}, p2{p2}, p3{p3}, k{k} {

    populateLUT();
//    this->k = k;
}

void Spline::populateLUT () {
    float step = 1.f / AMOUNT_OF_SAMPLES;

//    std::array<float, AMOUNT_OF_SAMPLES> timeLUT;
    lengthLUT[0] = 0;

    auto previous = apply(0);
    for (float t = step ; t < 1 ; t += step) {
        auto point = apply(t);
        lengthLUT[t * AMOUNT_OF_SAMPLES] = glm::length(previous - point) + lengthLUT[(t - step) * AMOUNT_OF_SAMPLES];
        previous = point;
    }

//    for (int i = 0 ; i < AMOUNT_OF_SAMPLES ; ++i) {
//        std::cout << lengthLUT[i] << ", ";
//    }
//    std::cout << std::endl;
}


glm::vec3 Spline::apply (float t) const {
    t = std::clamp(t, 0.0f, 1.0f);

//    float t0 = -std::pow(t, 3) + 3 * std::pow(t, 2) - 3 * t + 1;
//    float t1 = 3 * std::pow(t, 3) - 6 * std::pow(t, 2) + 3 * t;
//    float t2 = -3 * std::pow(t, 3) + 3 * std::pow(t, 2);
//    float t3 = std::pow(t, 3);
//
//    float Dt0 = -3 * std::pow(t, 2) + 6 * t - 3;
//    float Dt1 = 9 * std::pow(t, 2) - 12 * t + 3;
//    float Dt2 = -9 * std::pow(t, 2) + 6 * t;
//    float Dt3 = 3 * std::pow(t, 2);
//
//    float DDt0 = -6 * t + 6;
//    float DDt1 = 18 * t - 12;
//    float DDt2 = -18 * t + 6;
//    float DDt3 = 6 * t;

//    auto position = t0 * p0 + t1 * p1 + t2 * p2 + t3 * p3;
//    auto direction = glm::normalize(Dt0 * p0 + Dt1 * p1 + Dt2 * p2 + Dt3 * p3) * k + glm::normalize(DDt0 * p0 + DDt1 * p1 + DDt2 * p2 + DDt3 * p3) * (1 - k);
//
//    return {position, direction};

//    const glm::vec3& value = glm::catmullRom(p0, p1, p2, p3, t);

    return glm::catmullRom(p0, p1, p2, p3, t);

//    float epsilon = std::numeric_limits<float>::epsilon() * 10000;
//    return {
//            value,
////            (glm::catmullRom(p0, p1, p2, p3, t) - glm::catmullRom(p0, p1, p2, p3, t - epsilon)) / epsilon
//    };
}

glm::vec3 Spline::applyDistance (float d) const {
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

float Spline::advance (float oldT, float deltaT) {
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

float Spline::length () const {
    return lengthLUT[AMOUNT_OF_SAMPLES - 1];
}

std::ostream& operator<< (std::ostream& os, Spline bezier) {
//    os << "Spline{" << bezier.p0 << ", " << bezier.p1 << ", " << bezier.p2 << ", " << bezier.p3 << "}";
    os << bezier.p0.x << "," << bezier.p0.y << std::endl;
    os << bezier.p1.x << "," << bezier.p1.y << std::endl;
    os << bezier.p2.x << "," << bezier.p2.y << std::endl;
    os << bezier.p3.x << "," << bezier.p3.y;
    return os;
}


SplineSequence::SplineSequence (const std::vector<glm::vec3>& points, const float k) : curves{} {
    for (int i = 1 ; i < points.size() - 2 ; ++i) {
        curves.push_back(Spline{points[i - 1], points[i], points[i + 1], points[i + 2], k});
//        std::cout << curves.back() << std::endl;
//        curves.emplace_back(originPoints[i], originPoints[i] + controlPoints[i], originPoints[i + 1], originPoints[i + 1] + controlPoints[i + 1], k);
    }

    populateLenghts();

//    std::exit(0);
}

void SplineSequence::populateLenghts () {
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

glm::vec3 SplineSequence::getPoint (float t, bool compensateDistance) {
    t = std::clamp(t, 0.f, 1.f - std::numeric_limits<float>::epsilon());
    auto step = 1.f / curves.size();


    const Spline& spline = curves[static_cast<int>((t - std::numeric_limits<float>::epsilon()) * curves.size())];
    if (compensateDistance) {
        return spline.applyDistance(std::fmod(t, step) / step);
    } else {
        return spline.apply(std::fmod(t, step) / step);
    }
}

glm::vec3 SplineSequence::getPoint(float t) {
    return getPoint(t, false);
}

Ray SplineSequence::apply (float t, bool compensateDistance) {
    t = std::clamp(t, 0.f, 1.f - std::numeric_limits<float>::epsilon());
    float d = 1.f;

    return {getPoint(t, compensateDistance), (getPoint(t + d, compensateDistance) - getPoint(t, compensateDistance)) / d};
//    auto step = 1.f / curves.size();
//    return curves[static_cast<int>((t - std::numeric_limits<float>::epsilon()) * curves.size())].apply(std::fmod(t, step) / step);
}

float SplineSequence::length () {
    return lengths[AMOUNT_OF_SAMPLES - 1];
}
//
//Ray SplineSequence::applyDistance (float d) {
//    auto index = std::lower_bound(lengths.begin(), lengths.end(), d) - lengths.begin();
//
//    float actualLength = lengths[index] - lengths[index - 1];
//    return curves[index - 1].applyDistance((d - lengths[index - 1]) / actualLength);
//}

float SplineSequence::advance (float oldT, float deltaT) {
    return oldT + deltaT;
//    auto step = 1.f / curves.size();
//    return curves[static_cast<int>((oldT - std::numeric_limits<float>::epsilon()) * curves.size())].advance(std::fmod(oldT, step) / step, deltaT);
}

SplineSequence SplineSequence::getRandomSequence (int length, glm::vec3 origin = {0, 0, 0}) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator{seed};

    std::uniform_real_distribution<float> d(10, 20);
    std::uniform_real_distribution<float> angleDistribution(- M_PI / 2, M_PI / 2);

    std::vector<glm::vec3> originPoints;
    std::vector<glm::vec3> controlPoints;

    originPoints.push_back(origin);
    originPoints.push_back(origin + glm::vec3{1, 0, 0});
    for (int i = 0 ; i < length + 1 ; ++i) {


        const glm::vec3& straightDirection = originPoints[originPoints.size() - 1] - originPoints[originPoints.size() - 2];
        float newLength = d(generator);
//        originPoints.push_back(originPoints.back() + (glm::normalize(VectorOperations::rotateInsideCone(straightDirection, 0.5f)) * newLength));
        originPoints.push_back(originPoints.back() + (glm::normalize(VectorOperations::rotate(straightDirection, angleDistribution(generator), 0)) * newLength));
//        controlPoints.push_back(glm::normalize(VectorOperations::rotateInsideCone((controlPoints[originPoints.size() - 2] - controlPoints[originPoints.size() - 1]), 10)));
    }

    for (auto& point : originPoints) {
        point.z = 1;
    }

    for (auto& point : controlPoints) {
//        point.z = ;
    }

//    return CubicBezierSequence;
    return {originPoints, 1.f};
}

std::ostream& operator<< (std::ostream& os, SplineSequence sequence) {
    for (int i = 0 ; i < sequence.curves.size() ; ++i) {
//        std::cout << i << std::endl;
        os << sequence.curves[i] << std::endl;
    }

    return os;
}

