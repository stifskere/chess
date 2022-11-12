cmake_minimum_required(VERSION 3.23)
project(Chess)

add_definitions(-DSFML_STATIC)

set(CMAKE_EXE_LINKER_FLAGS "-O3 -static-libgcc -static-libstdc++ -static")
set(CMAKE_CXX_STANDARD 17)

link_directories(lib)
include_directories(include)

add_executable(Chess WIN32 main.cpp position.h eventHandler.h piece.h enums.h string_utilities.h table_data.h table.h)
target_link_libraries(Chess sfml-graphics-s sfml-main sfml-window-s sfml-system-s winmm opengl32 freetype)