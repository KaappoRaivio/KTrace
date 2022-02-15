//
// Created by kaappo on 15.2.2022.
//

#pragma once

#include "Scene.h"

namespace Scenes {


    Scene getSceneOne (int viewport_side_length);
    Scene getSceneTwo (int viewport_side_length);
    Scene getSceneThree (int viewport_side_length);
    Scene getDebug (int viewportSideLength);

    template <int INDEX>
    Scene getScene (int viewportSideLength) {
        switch (INDEX) {
            case 0:
                return getDebug(viewportSideLength);
            case 1:
                return getSceneOne(viewportSideLength);
            case 2:
                return getSceneTwo(viewportSideLength);
            case 3:
                return getSceneThree(viewportSideLength);
        }
    }

}



