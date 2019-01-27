#include <utils.h>

#include <X11/Xlib.h>
#include <X11/Xlibint.h>
#include <X11/Xproto.h>
#include <X11/Xatom.h>
#include <X11/extensions/Xrandr.h>

std::vector<std::string> i3ScreenManager::utils::getAllEDIDs(std::string display_name) {

    // TODO: Handle errors if we can't get the screen, properties, etc.

    // Get the root window, which should extend over all screens
    Display* display = XOpenDisplay(display_name.c_str());
    int default_screen = DefaultScreen(display);
    Window root = RootWindow(display, default_screen);

    // Get info about all the screens
    XRRScreenResources* resources = XRRGetScreenResourcesCurrent (display, root);

    // Iterate over all the screens, getting the EDID for each
    // NOTE: An "output" here is like a port on your computer, ex. "DP1", "eDP1", etc.
    std::vector<std::string> eeids;
    for (int output_index = 0; output_index < resources->noutput; output_index++){
        RROutput output = resources->outputs[output_index];
        XRROutputInfo* output_info = XRRGetOutputInfo (display, resources, output);

        int num_of_props;
        Atom* props = XRRListOutputProperties (display, output,
                                         &num_of_props);
        for (int prop_index; prop_index < num_of_props; prop_index++){
            Atom prop = props[prop_index];
            char* atom_name = XGetAtomName (display, prop);

            //if (strcmp (atom_name, "EDID") == 0) {
            //    eeids.emplace_back(std::string(atom))
            //}
        }
    }
}
