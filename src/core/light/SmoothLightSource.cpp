//
// Created by kaappo on 16.9.2021.
//

#include "SmoothLightSource.h"

SmoothLightSource::SmoothLightSource (const double radius, const int amountOfLightSources, const LightSource& masterLightSource) : radius(radius), amountOfLightSources(amountOfLightSources), masterLightSource(masterLightSource) {}

std::vector<LightSource> SmoothLightSource::approximate () const {
    std::vector<LightSource> lights;

    for (int i = 0; i < amountOfLightSources; ++i) {
        MyVector3 v = masterLightSource.position + MyVector3::randomInsideUnitSphere() * radius;
        lights.emplace_back(v, masterLightSource.intensity / amountOfLightSources, 0);
    }

    return lights;
}
