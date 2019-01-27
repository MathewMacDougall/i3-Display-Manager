cmake_minimum_required(VERSION 3.13)
project(i3-display-manager)

set(CMAKE_CXX_STANDARD 17)

# GTest Setup
include(gtest.cmake)
set(TESTING_LIBS gtest pthread)
enable_testing()

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR})

# Find and link the X11 and Xrandr libraries
find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})
find_package(Xrandr REQUIRED)
link_libraries(${XRANDR_LIBRARIES})

include_directories(./include
        /usr/include/X11/extensions
        ${X11_INCLUDE_DIR})

# Find Source Files
FILE(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(i3-display-manager src/main.cpp
        ${SRC_FILES}
        )

# Find Test Files
FILE(GLOB_RECURSE TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

# Build the test executable
add_executable(all_tests
        test/ScreenTest.cpp
    ${TEST_FILES}
    ${HEADER_FILES}
)
target_link_libraries(all_tests ${TESTING_LIBS})
