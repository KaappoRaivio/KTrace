//
// Created by kaappo on 15.2.2022.
//

#pragma once

#include "Scene.h"

namespace Scenes {


    Scene getSceneOne (int windowX, int windowY);
    Scene getSceneTwo (int windowX, int windowY);
    Scene getSceneThree (int windowX, int windowY);
    Scene getDebug (int windowX, int windowY);
    Scene getSceneFour (int windowX, int windowY);

    Scene getRaytracinginaweekendtestscene (int windowX, int windowY);
    Scene getBezierScene (int windowX, int windowY, const SplineSequence& sequence);

    template <int INDEX>
    Scene getScene (int windowX, int windowY) {
        switch (INDEX) {
            case 0:
                return getDebug(windowX, windowY);
            case 1:
                return getSceneOne(windowX, windowY);
            case 2:
                return getSceneTwo(windowX, windowY);
            case 3:
                return getSceneThree(windowX, windowY);
            case 4:
                return getSceneFour(windowX, windowY);
            case 5:
                return getRaytracinginaweekendtestscene(windowX, windowY);
//            case 6:
//                return getBezierScene(windowX, windowY, SplineSequence(std::vector(), 0));
        }
    }


}



