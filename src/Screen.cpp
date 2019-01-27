#include "Screen.h"
#include <Xrandr.h>
#include <iostream>
#include <cstring>
#include <cinttypes>
#include <utils.h>
#include <DisconnectedOutputException.h>

namespace i3ScreenManager {
    Screen::Screen(Display *x_display_pointer, XRRScreenResources *x_screen_resources, RROutput output) {
        this->x_display_pointer = x_display_pointer;
        this->x_screen_resources = x_screen_resources;
        this->output = output;
        this->screen_properties = Screen::getScreenProperties(x_display_pointer, output);
    }

    EDID Screen::getEDID() const {
        return screen_properties.edid;
    }

    Display* Screen::getRawDisplayPtr() const {
        return x_display_pointer;
    }

    RROutput Screen::getRROutput() const {
        return output;
    }

    ScreenProperties Screen::getScreenProperties(Display *x_display_pointer, RROutput output) {
        ScreenProperties screen_properties;

        int num_of_props;
        Atom* props = XRRListOutputProperties (x_display_pointer, output,
                                               &num_of_props);

        for (int prop_index = 0; prop_index < num_of_props; prop_index++){
            Atom prop = props[prop_index];
            char* atom_name = XGetAtomName (x_display_pointer, prop);

            // Check if this property is the EDID
            if (strcmp (atom_name, "EDID") == 0) {
                screen_properties.edid = i3ScreenManager::utils::getEDID(x_display_pointer, output, prop);
            }
        }

        if (screen_properties.edid == ""){
            // TODO: Figure out some sort of actually half-decent check for this shit
            throw DisconnectedOutputException();
        }

        return screen_properties;
    }

}