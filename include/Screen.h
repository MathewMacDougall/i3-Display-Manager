#pragma once

#include <string>
#include <X11/Xlib.h>
#include <Xrandr.h>
#include <vector>

namespace i3ScreenManager {

    typedef std::string EDID;

    /**
     * A convenient datatype to represent the different orientations a Screen can have
     */
    enum ScreenRotation{
        NORMAL=1,
        LEFT=2,
        RIGHT=8,
        INVERTED=4
    };

    /**
     * Contains all the properties for a Screen that we care about
     */
    struct ScreenProperties {
        // A unique value for this Screen/Monitor
        EDID edid;
    };

    class Screen {
    public:
        Screen() = delete;

        /**
         * Constructs a new Screen object
         *
         * @param x_display_pointer A raw pointer to the X display this Screen is a part of
         * @param x_screen_resources The X screen resources for this Screen
         * @param output The RROutput that corresponds to this Screen. This is the approximate
         * equivalent of a "Screen/Monitor" in X
         */
        explicit Screen(Display *x_display_pointer, XRRScreenResources *x_screen_resources, RROutput output);

        /**
         * Returns the EDID of this Screen. The EDID is a unique value for the Screen.
         * @return the EDID of this Screen.
         */
        EDID getEDID() const;

        /**
         * Returns the raw pointer to the Display this Screen is a part of
         * @return the raw pointer to the Display this Screen is a part of
         */
        Display* getRawDisplayPtr() const;

        /**
         * Returns the RROutput associated with this Screen. The RROutput is roughly the
         * equivalent of this Screen/Monitor in X
         * @return the RROutput associated with this Screen
         */
        RROutput getRROutput() const;

    private:
        /**
         * Returns a ScreenProperties struct containing all the properties we care about
         * for a given Screen
         *
         * @param x_display_pointer A raw pointer to the X Display that contains the Screen
         * we want the properties from
         * @param output The RROutput container associated with the Screen we want to get
         * properties from.
         * @return A ScreenProperties struct containing all the properties we care about for
         * the specified Screen
         */
        static ScreenProperties getScreenProperties(Display *x_display_pointer, RROutput output);

        // A raw pointer to the X Display this Screen is a part of
        Display *x_display_pointer;
        // The X screen resources for this Screen
        // TODO: Might be able to be removed
        XRRScreenResources *x_screen_resources;
        // The RROutput associated with this Screen. An RROutput is the rough equivalent
        // to a Screen/Monitor in the X system
        RROutput output;
        // The properties for this screen
        ScreenProperties screen_properties;
    };
}
