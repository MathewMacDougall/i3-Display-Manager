#pragma once

#include <string>
#include <X11/Xlib.h>

namespace i3ScreenManager {

    typedef std::string EDID;

    enum ScreenRotation{
        NORMAL=1,
        LEFT=2,
        RIGHT=8,
        INVERTED=4
    };

    class Screen {
    public:
        explicit Screen(std::string display_name, EDID edid);

        void setResolution(unsigned int x_pixels, unsigned int y_pixels);

    private:
        Display *dpy;
        int screen;
        Window root;

        std::string display_name;
        EDID edid;

    };
}
