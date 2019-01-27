#include <Display.h>

#include <DisconnectedOutputException.h>


i3ScreenManager::Display::Display(std::string x_display_name) {

    // TODO: Check for and handle failures, like if there is no display with the given name

    // Get the display we're supposed to be wrapping
    x_display_ptr = XOpenDisplay(x_display_name.c_str());

    // Get the root window, which should extend over all screens
    Window root = getRootWindow();

    // Get info about all the screens
    XRRScreenResources* screen_resources = XRRGetScreenResourcesCurrent (x_display_ptr, root);

    // Create a Screen for each output
    for (int output_index = 0; output_index < screen_resources->noutput; output_index++){
        RROutput output = screen_resources->outputs[output_index];
        try{
            screens.emplace_back(Screen(x_display_ptr, screen_resources, output));
        } catch (DisconnectedOutputException err) {
            // We tried to construct a screen from an output that isn't connected
        }
    }

}

_XDisplay* i3ScreenManager::Display::getXDisplayPtr() {
    return x_display_ptr;
}

Window i3ScreenManager::Display::getRootWindow() {
    int default_screen = DefaultScreen(x_display_ptr);
    return RootWindow(x_display_ptr, default_screen);
}
