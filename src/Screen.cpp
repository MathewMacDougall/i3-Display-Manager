#include "Screen.h"
#include <Xrandr.h>
#include <iostream>
#include <cstring>
#include <cinttypes>
#include <DisconnectedOutputException.h>

namespace i3ScreenManager {
    Screen::Screen(Display *x_display_pointer, Window window, XRRScreenResources *x_screen_resources, RROutput output) {
        this->x_display_pointer = x_display_pointer;
        this->window = window;
        this->x_screen_resources = x_screen_resources;
        this->output = output;
        this->screen_properties = Screen::getScreenProperties(x_display_pointer, output);

        XRRScreenConfiguration* sc = XRRGetScreenInfo(x_display_pointer, window);
        Rotation current_rotation;
        Rotation r = XRRConfigRotations(sc, &current_rotation);
        this->screen_properties.screen_rotation = Screen::getScreenRotationFromXRotation(current_rotation);

        int nsizes;
        XRRScreenSize *ss = XRRConfigSizes(sc, &nsizes);

        this->screen_properties.physical_dimensions = Screen::getPhysicalDimensionsFromScreenSize(ss);
        // TODO: Note the pixel dimensions are not the resolution the screen is currently set to
        // It's the maximum resolution / dimension in pixels
        this->screen_properties.pixel_dimensions = Screen::getPixelDimensionsFromScreenSize(ss);

        volatile int i = 0;

    }

    EDID Screen::getEDID() const {
        return screen_properties.edid;
    }

    Display* Screen::getRawDisplayPtr() const { return x_display_pointer;
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
                screen_properties.edid = Screen::getRawPropData(
                        x_display_pointer, output, prop);
            }
            else if (strcmp (atom_name, "scaling mode") == 0) {

                std::string data = Screen::getRawPropData(
                        x_display_pointer, output, prop);
                std::cout << atom_name << " - " << data << std::endl;

            }
            else if (strcmp (atom_name, "Broadcast RGB") == 0) {
                // TODO
                std::string data = Screen::getRawPropData(
                        x_display_pointer, output, prop);
                std::cout << atom_name << " - " << data << std::endl;
            }
            else if (strcmp (atom_name, "audio") == 0) {
                // TODO
                std::string data = Screen::getRawPropData(
                        x_display_pointer, output, prop);
                std::cout << atom_name << " - " << data << std::endl;
            }
            else if (strcmp (atom_name, "non-desktop") == 0) {
                // TODO
                std::string data = Screen::getRawPropData(
                        x_display_pointer, output, prop);
                std::cout << atom_name << " - " << data << std::endl;
            }
            else if (strcmp (atom_name, "link-status") == 0) {
                // TODO
                std::string data = Screen::getRawPropData(
                        x_display_pointer, output, prop);
                std::cout << atom_name << " - " << data << std::endl;
            }
            else if (strcmp (atom_name, "aspect ratio") == 0) {
                // TODO
                std::string data = Screen::getRawPropData(
                        x_display_pointer, output, prop);
                std::cout << atom_name << " - " << data << std::endl;
            }
            else {
                std::cerr << "Unexpected atom name: " << atom_name << std::endl;
                std::abort();
            }
        }

        if (screen_properties.edid == ""){
            // TODO: Figure out some sort of actually half-decent check for this shit
            throw DisconnectedOutputException();
        }

        return screen_properties;
    }

    EDID Screen::getRawPropData(Display *x_display_pointer, RROutput output, Atom prop) {
        // Grab the actual data
        unsigned char *raw_prop_data;
        int actual_format;
        unsigned long nitems, bytes_after;
        Atom actual_type;
        int prop_data_index;
        XRRGetOutputProperty (x_display_pointer, output, prop,
                              0, 100, False, False,
                              AnyPropertyType,
                              &actual_type, &actual_format,
                              &nitems, &bytes_after, &raw_prop_data);

        // Construct the EDID from the raw data
        i3ScreenManager::EDID edid;
        for (prop_data_index = 0; prop_data_index < nitems; prop_data_index++)
        {
            // TODO: the following commented out code causes a segfault, but a malloc of size 0 doesn't? what the literal fuck
            //static char *s = 0;
            static char *s = (char*)malloc(sizeof(char) * 0);
            sprintf(s, "%02" PRIX8, raw_prop_data[prop_data_index]);
            edid.append(s);
        }

        return edid;
    }

    ScreenRotation Screen::getScreenRotationFromXRotation(
            Rotation rotation) {
        // TODO: The LEFT and RIGHT rotations may be reversed here. Needs testing
        if(rotation == RR_Rotate_0) {
            return i3ScreenManager::ScreenRotation::NORMAL;
        }
        else if(rotation == RR_Rotate_90) {
            return i3ScreenManager::ScreenRotation::LEFT;
        }
        else if(rotation == RR_Rotate_180) {
            return i3ScreenManager::ScreenRotation::INVERTED;
        }
        else if(rotation == RR_Rotate_270) {

            return i3ScreenManager::ScreenRotation::RIGHT;
        }
        else {
            std::abort();
        }
    }

    PhysicalScreenDimensions Screen::getPhysicalDimensionsFromScreenSize(
            XRRScreenSize *screen_size) {
        PhysicalScreenDimensions physical_dimensions;
        physical_dimensions.width_millimeters = static_cast<unsigned int>(screen_size->mwidth);
        physical_dimensions.height_millimeters = static_cast<unsigned int>(screen_size->mheight);
        return physical_dimensions;
    }

    PixelScreenDimensions Screen::getPixelDimensionsFromScreenSize(
            XRRScreenSize *screen_size) {
        PixelScreenDimensions pixel_dimensions;
        pixel_dimensions.width_pixels = static_cast<unsigned int>(screen_size->width);
        pixel_dimensions.heigh_pixels = static_cast<unsigned int>(screen_size->height);
        return pixel_dimensions;
    }
}