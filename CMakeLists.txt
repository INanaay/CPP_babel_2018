cmake_minimum_required(VERSION 3.12)
project(CPP_babel_2018)

set(CMAKE_CXX_STANDARD 14)

LINK_DIRECTORIES(deps/libs)
INCLUDE_DIRECTORIES(deps/incs)

add_executable(CPP_babel_2018
        server/main.cpp)

TARGET_LINK_LIBRARIES(CPP_babel_2018
        Qt5Core)
