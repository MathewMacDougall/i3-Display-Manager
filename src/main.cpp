#include <iostream>

#include <ScreenManager.h>

// Callback:
//     display = Display()
//     display.setupScreensFromConfig(Config config)

int main(int argc, char** argv){
    std::cout << "Hello World" << std::endl;

    // TODO: somehow get the display... maybe from environment variable? Or maybe as a command line arg
    i3ScreenManager::ScreenManager screenManager(":0");

    screenManager.controlLoop();
}