cmake_minimum_required(VERSION 3.8)
project(GLIDER)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-O2 -ggdb")


add_executable(Glider main.cpp menu_components.cpp build_menu.cpp build_components.cpp game_objects.cpp level_selection_menu.cpp game_menu.cpp player.cpp)

set(SFML_DIR "C:/Users/Ruslan/CLionProjects/lib/sfml/GCC 7.3.0 MinGW (SEH) - 64-bit/SFML-2.5.1/lib/cmake/SFML")

target_link_libraries (Glider sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML 2.5 REQUIRED graphics network audio window system)