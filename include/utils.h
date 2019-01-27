#pragma once

#include <Screen.h>
#include <vector>

namespace i3ScreenManager {
    namespace utils {

        /**
         * Gets the EDID for every screen attached to this system
         *
         * @param display_name the name of the display to get the screens from
         * (ex. ":0")
         * @return all the EDID's for screens attached to this computer
         */
        std::vector<std::string> getAllEDIDs(std::string display_name);
    }
};