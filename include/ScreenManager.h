#pragma once

#include <string>
#include <Display.h>

namespace i3ScreenManager{
    /**
     * Create a ScreenManager from a given X display name
     */
    class ScreenManager{
    public:
        /**
         * Create a screen manager for a given X display
         * @param x_display_name the name of the display to get the screens from
         * (ex. ":0")
         */
        ScreenManager(std::string x_display_name);

        // TODO: better function here
        /**
         * This function will block forever, it contains all the logic for
         * managing screens
         */
        void controlLoop();

    private:

        /**
         * Handle any monitor changes that occur. This function should be called
         * whenever a monitor change occurs
         */
        void handleMonitorChange();

        // The name of the X display that we're managing
        std::string x_display_name;

        // The X display that we're managing
        i3ScreenManager::Display display;
    };
}