cmake_minimum_required(VERSION 3.21)
project(TEST)

set(CMAKE_CXX_STANDARD 14)

add_executable(TEST main.cpp Player.hpp Tile.hpp Background.hpp Button.hpp Button.cpp Background.cpp Tile.cpp Player.cpp)

set(SFML_DIR "C:/Users/Ruslan/CLionProjects/lib/sfml/GCC 7.3.0 MinGW (SEH) - 64-bit/SFML-2.5.1/lib/cmake/SFML")

target_link_libraries (TEST sfml-graphics)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")

find_package(SFML 2.5 REQUIRED graphics network audio window system)


