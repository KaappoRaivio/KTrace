//
// Created by kaappo on 13.9.2021.
//

#include "IntensityBlend.h"

void IntensityBlend::operator+= (const Intensity& color) {
    blend.push_back(color);
}

Intensity IntensityBlend::commitSum () const {
    Intensity result{0, 0, 0};
    for (const auto& item : blend) {
        result += item;
    }

    return result;
}

Intensity IntensityBlend::commitBlend () const {
    return commitSum() / std::max((unsigned long) 1, blend.size());
}

void IntensityBlend::operator+= (const IntensityBlend& color) {
    for (const auto& item : color.blend) {
        *this += item;
    }
}
