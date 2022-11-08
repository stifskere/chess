cmake_minimum_required(VERSION 3.23)
project(Chess)

set(CMAKE_CXX_STANDARD 17)

link_directories(lib)
include_directories(include)

add_executable(Chess main.cpp position.h eventHandler.h piece.h enums.h string_utilities.h)
target_link_libraries(Chess sfml-graphics sfml-window sfml-system)
