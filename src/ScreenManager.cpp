#include <ScreenManager.h>

i3ScreenManager::ScreenManager::ScreenManager(std::string x_display_name) :
x_display_name(x_display_name),
display(x_display_name)
{}

void i3ScreenManager::ScreenManager::controlLoop() {
    // TODO: Error checking for if we can't get the extension here

    // TODO: we don't need this now.... but would be good to use it in the future, see the xrandr command line utility for examples.........
    // Get the offsets to allow us to construct XRandr events from XLib events
    int event_base, error_base;
    XRRQueryExtension(display.getXDisplayPtr(), &event_base, &error_base);

    // This infinite loop keeps us waiting for any X events
    XEvent event;
    while(true) {
        // TODO: We don't need to do this every time.... just whenever we detect a monitor change and re-create the display object
        // Setup X notifications so we can receive any events (like monitors being
        // plugged/unplugged) that happen
        // TODO: Change the mask so we only receive monitor events!! (https://tronche.com/gui/x/xlib/events/processing-overview.html)
        XSelectInput(display.getXDisplayPtr(), display.getRootWindow(), StructureNotifyMask);

        // Blocking call that will return on a new event
        XNextEvent(display.getXDisplayPtr(), &event);

        // TODO: remove this
        printf("Event received, type = %d\n", event.type);

        // TODO: we don't need this now.... but would be good to use it in the future, see the xrandr command line utility for examples.........
        /* update Xlib's knowledge of the event */
        XRRUpdateConfiguration(&event);

        // TODO: We should figure out what event to actually check. No idea why, but 33 fires whenever we plug/unplug a monitor..........
        switch (event.type){
            case 33:
                handleMonitorChange();
        }

    }
}

void i3ScreenManager::ScreenManager::handleMonitorChange() {
    // TODO: better comment here
    // Re-create the display object (using the same display)
    display = Display(x_display_name);

    // TODO: Setup screens from config here!
}
