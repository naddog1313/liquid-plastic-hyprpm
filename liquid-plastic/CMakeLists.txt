cmake_minimum_required(VERSION 3.27)
project(liquid-plastic)

set(CMAKE_CXX_STANDARD 23)

add_library(liquid-plastic SHARED main.cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(deps REQUIRED IMPORTED_TARGET
    hyprland
    pixman-1
    libdrm
    xkbcommon
    hyprlang
)

target_link_libraries(liquid-plastic PRIVATE PkgConfig::deps)
