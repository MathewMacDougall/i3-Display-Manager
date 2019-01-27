#pragma once

#include <Screen.h>
#include <vector>
#include <string>
#include <randr.h>

namespace i3ScreenManager {
    namespace utils {

        /**
         * Gets the EDID for every screen attached to this system
         *
         * @param display_name the name of the display to get the screens from
         * (ex. ":0")
         * @return all the EDID's for screens attached to this computer
         */
        std::vector<i3ScreenManager::EDID> getAllEDIDs(std::string display_name);


        ScreenRotation getScreenRotationFromXRotation(Rotation rotation);
    }
};