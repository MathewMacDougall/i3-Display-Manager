#include <utils.h>

// TODO: Can we get rid of some of these includes?
#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xproto.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xrandr.h>
#include <cinttypes>
#include <stdlib.h>

std::vector<i3ScreenManager::EDID> i3ScreenManager::utils::getAllEDIDs(std::string display_name) {

    // TODO: Handle errors if we can't get the screen, properties, etc.

    // Get the root window, which should extend over all screens
    Display* display = XOpenDisplay(display_name.c_str());
    int default_screen = DefaultScreen(display);
    Window root = RootWindow(display, default_screen);

    // Get info about all the screens
    XRRScreenResources* screen_resources = XRRGetScreenResourcesCurrent (display, root);

    // Iterate over all the screens, getting the EDID for each
    // NOTE: An "output" here is like a port on your computer, ex. "DP1", "eDP1", etc.
    std::vector<i3ScreenManager::EDID> edids;
    for (int output_index = 0; output_index < screen_resources->noutput; output_index++){
        RROutput output = screen_resources->outputs[output_index];
        XRROutputInfo* output_info = XRRGetOutputInfo (display, screen_resources, output);

        int num_of_props;
        Atom* props = XRRListOutputProperties (display, output,
                                         &num_of_props);
        for (int prop_index = 0; prop_index < num_of_props; prop_index++){
            Atom prop = props[prop_index];
            char* atom_name = XGetAtomName (display, prop);

            // Check if this property is the EDID
            if (strcmp (atom_name, "EDID") == 0) {

                // Grab the actual data
                unsigned char *raw_prop_data;
                int actual_format;
                unsigned long nitems, bytes_after;
                Atom actual_type;
                XRRPropertyInfo *propinfo;
                int prop_data_index;
                XRRGetOutputProperty (display, output, prop,
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
                edids.emplace_back(edid);
            }
        }
    }

    XRRFreeScreenResources(screen_resources);

    return edids;
}
