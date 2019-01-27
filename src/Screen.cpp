#include "Screen.h"
#include <Xrandr.h>
#include <iostream>

namespace i3ScreenManager {
    Screen::Screen(std::string display_name, EDID edid) : display_name(display_name), edid(edid) {
        volatile std::string foo = "foo";
        dpy = XOpenDisplay(this->display_name.c_str());

        if(dpy == NULL) {
            std::cerr << "Can't open display " << XDisplayName(display_name.c_str()) << std::endl;
            std::abort();
        }

        screen = DefaultScreen(dpy);
        root = RootWindow(dpy, screen);
    }

    void Screen::setResolution(unsigned int x_pixels, unsigned int y_pixels) {
        XRRScreenConfiguration * sc = XRRGetScreenInfo(dpy, root);
        Rotation current_rotation;
        SizeID current_size = XRRConfigCurrentConfiguration(sc, &current_rotation);



        volatile int i = 0;
    }
}