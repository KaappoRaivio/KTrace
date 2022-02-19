//
// Created by kaappo on 16.9.2021.
//

#pragma once


#include <vector>
#include "../common/LightSource.h"

class SmoothLightSource {
private:
    const float radius;
    const int amountOfLightSources;
    const LightSource& masterLightSource;
public:
    SmoothLightSource (float radius, int amountOfLightSources, const LightSource& masterLightSource);

    std::vector<LightSource> approximate () const;
};



