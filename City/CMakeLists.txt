cmake_minimum_required(VERSION 3.21)
project(City)

set(CMAKE_CXX_STANDARD 14)

add_executable(City main.cpp Button.hpp Background.hpp Moveground.hpp Player.hpp Column.hpp Column.cpp Player.cpp Moveground.cpp Button.cpp Background.cpp)

set(SFML_DIR "C:/Users/Ruslan/CLionProjects/lib/sfml/GCC 7.3.0 MinGW (SEH) - 64-bit/SFML-2.5.1/lib/cmake/SFML")

target_link_libraries (City sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML 2.5 REQUIRED graphics network audio window system)

