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
    Scene getSceneFour (int viewport_side_length);

    Scene getRaytracinginaweekendtestscene (int viewportSideLength);

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
            case 4:
                return getSceneFour(viewportSideLength);
            case 5:
                return getRaytracinginaweekendtestscene(viewportSideLength);
        }
    }


}



