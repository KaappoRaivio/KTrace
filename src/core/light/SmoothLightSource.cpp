//
// Created by kaappo on 16.9.2021.
//

#include <glm/gtc/random.hpp>
#include "SmoothLightSource.h"

SmoothLightSource::SmoothLightSource (const float radius, const int amountOfLightSources, const LightSource& masterLightSource) : radius(radius), amountOfLightSources(amountOfLightSources), masterLightSource(masterLightSource) {}

std::vector<LightSource> SmoothLightSource::approximate () const {
    std::vector<LightSource> lights;

    for (int i = 0; i < amountOfLightSources; ++i) {
        glm::vec3 v = masterLightSource.position + radius * glm::sphericalRand(1.0f);
        lights.emplace_back(v, masterLightSource.intensity / amountOfLightSources, 0);
    }

    return lights;
}
