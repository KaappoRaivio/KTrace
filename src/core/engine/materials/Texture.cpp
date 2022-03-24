//
// Created by kaappo on 21.9.2021.
//

#include "Texture.h"

std::ostream& operator<< (std::ostream& os, const Texture& texture) {
    return texture.print(os);
}
