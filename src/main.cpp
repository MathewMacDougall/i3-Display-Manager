#include <iostream>
#include "Screen.h"
#include <string>

int main(int argc, char** argv){
    i3ScreenManager::EDID edid = "test EDID";
    std::string display_name = ":0";
    i3ScreenManager::Screen screen = i3ScreenManager::Screen(display_name, edid);
    screen.setResolution(0, 0);

    std::cout << "Hello World" << std::endl;
}
