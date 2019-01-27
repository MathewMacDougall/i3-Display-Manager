#include <iostream>
#include <utils.h>

int main(int argc, char** argv){
    std::cout << "Hello World" << std::endl;

    i3ScreenManager::utils::getAllEDIDs(":0");
}