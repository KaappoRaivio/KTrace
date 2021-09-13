//
// Created by kaappo on 13.9.2021.
//

#pragma once


#include <vector>
#include "Intensity.h"

class IntensityBlend {
private:
    std::vector<Intensity> blend;

public:
    IntensityBlend () = default;

    void operator += (const Intensity& color);
    [[nodiscard]] Intensity commit_blend() const;
};



