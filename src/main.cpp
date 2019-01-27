#include <iostream>
#include "Screen.h"
#include <string>

#include <ScreenManager.h>

int main(int argc, char** argv){
    std::cout << "Hello World" << std::endl;

    // TODO: somehow get the display... maybe from environment variable? Or maybe as a command line arg
    i3ScreenManager::ScreenManager screenManager(":0");

    screenManager.controlLoop();
}
