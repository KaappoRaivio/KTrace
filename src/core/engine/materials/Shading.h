//
// Created by kaappo on 11.3.2022.
//

#pragma once


#include <glm/vec3.hpp>

namespace Shading {
    float lambertianDiffuseReflection (const glm::vec3& N, const glm::vec3& L, const glm::vec3& d);
    float calculateBeckmannDistribution (const glm::vec3& R, const glm::vec3& V, float roughness);
    float calculatePhongReflection (const glm::vec3& N, const glm::vec3& L, const glm::vec3& V, float alpha);
    float getReflectance (float cosine, float refractionRatio);
};



