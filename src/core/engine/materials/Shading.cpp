//
// Created by kaappo on 11.3.2022.
//

#include <glm/geometric.hpp>
#include "Shading.h"

float Shading::lambertianDiffuseReflection (const glm::vec3& N, const glm::vec3& L, const glm::vec3& d) {
    float dot1 = -glm::dot(d, N);
    float dot2 = glm::dot(L, N);

    if (dot2 > 0 and dot1 > 0) {
        return dot2;
    } else {
        return 0;
    }






//    return std::max(0.0, N * L);

    if ((dot2 < 0) == (dot1 < 0)) {
        return std::abs(glm::dot(N, L));
    } else {
        return 0;
    }

}

float Shading::calculateBeckmannDistribution (const glm::vec3& R, const glm::vec3& V, float roughness) {
    if (roughness == 0) {
        return 0;
    }

    float cosine = glm::dot(R, V);


    return std::exp(-(1 - std::pow(cosine, 2)) / (std::pow(cosine * roughness, 2))) / (M_PI * std::pow(roughness, 2) * std::pow(cosine, 4));
//    / (std::numbers::pi_v<float> * std::pow(roughness, 2) * std::pow(cosine, 4));


}

float Shading::getReflectance (float cosine, float refractionRatio) {
    // Use Schlick's approximation for reflectance.
    float r0 = glm::pow((1 - refractionRatio) / (1 + refractionRatio), 2);
    return r0 + (1 - r0) * glm::pow((1 - cosine), 5);
}
