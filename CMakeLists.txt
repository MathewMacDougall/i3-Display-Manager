cmake_minimum_required(VERSION 3.13)
project(i3-display-manager)

set(CMAKE_CXX_STANDARD 17)

# GTest Setup
include(gtest.cmake)
set(TESTING_LIBS gtest pthread)
enable_testing()

# Find and link the X11 libraries
find_package(X11 REQUIRED)
link_libraries(${X11_LIBRARIES})

include_directories(./include
        ${X11_INCLUDE_DIR})

add_executable(i3-display-manager src/main.cpp
        src/Screen.cpp)

# Find Test Files
FILE(GLOB_RECURSE TEST_FILES "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp")

# Build the test executable
add_executable(all_tests
        test/ScreenTest.cpp
    ${TEST_FILES}
    ${HEADER_FILES}
)
target_link_libraries(all_tests ${TESTING_LIBS})
