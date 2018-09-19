cmake_minimum_required(VERSION 3.9.1)
project(CPP_babel_2018)

set(CMAKE_CXX_STANDARD 14)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

LINK_DIRECTORIES(deps/libs)
INCLUDE_DIRECTORIES(deps/incs)

add_executable(CPP_babel_2018
        server/src/main.cpp)

TARGET_LINK_LIBRARIES(CPP_babel_2018
        ${CONAN_LIBS}
        )
