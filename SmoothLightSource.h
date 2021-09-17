//
// Created by kaappo on 16.9.2021.
//

#pragma once


#include <vector>
#include "LightSource.h"

class SmoothLightSource {
private:
    const double radius;
    const int amountOfLightSources;
    const LightSource& masterLightSource;
public:
    SmoothLightSource(double radius, int amountOfLightSources, const LightSource &masterLightSource);
    [[nodiscard]] std::vector<LightSource> approximate() const;
};



