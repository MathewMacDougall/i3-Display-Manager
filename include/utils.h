#pragma once

#include <Screen.h>
#include <vector>
#include <string>
#include <randr.h>

namespace i3ScreenManager {
    namespace utils {

        // TODO: Remove this
        /**
         * Gets the EDID for every screen attached to this system
         *
         * @param display_name the name of the display to get the screens from
         * (ex. ":0")
         * @return all the EDID's for screens attached to this computer
         */
//        std::vector<i3ScreenManager::EDID> getAllEDIDs(std::string display_name);

        /**
         * Extracts the EDID from the given prop
         *
         * @param x_display_pointer A raw pointer to the display
         * @param output The output that contains the prop
         * @param prop The Atom prop that contains the EDID
         * @return The EDID from the given prop
         */
        i3ScreenManager::EDID getEDID(Display *x_display_pointer, RROutput output, Atom prop);


        /**
         * Returns a ScreenRotation given a Rotation value for a screen
         *
         * @param rotation The Rotation value
         * @return The equivalent ScreenRotation of the given rotation
         */
        ScreenRotation getScreenRotationFromXRotation(Rotation rotation);
    }
};