cmake_minimum_required(VERSION 3.13)
project(i3-display-manager)

set(CMAKE_CXX_STANDARD 17)

include_directories(./include
        /usr/include/X11/extensions)

add_executable(i3-display-manager src/main.cpp
        src/Screen.cpp)