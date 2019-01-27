#pragma once

#include <string>
#include <vector>
#include <Screen.h>
#include <X11/extensions/Xrandr.h>

namespace i3ScreenManager {
    class Display {
    public:
        Display() = delete;

        /**
         * Construct a display from a given display name
         *
         * @param x_display_name the name of the display to get the screens from
         * (ex. ":0")
         */
        Display(std::string x_display_name);

        /**
         * Gets a pointer to the X display this class is wrapping
         *
         * @return a pointer to the X display this class is wrapping
         */
        _XDisplay* getXDisplayPtr();

        /**
         * Gets the root window for this display
         *
         * The root window is a window which is the parent of all other windows
         *
         * @return the root window for this display
         */
        Window getRootWindow();

    private:
        // A pointer to the X display that this class represents.
        // NOTE: We do *not* own the object this points to
        _XDisplay* x_display_ptr;

        // All the screens on this display
        std::vector<i3ScreenManager::Screen> screens;
    };
}

