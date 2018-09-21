cmake_minimum_required(VERSION 3.12)
project(CPP_babel_2018)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-lpthread")

LINK_DIRECTORIES(deps/libs)
INCLUDE_DIRECTORIES(deps/incs)
INCLUDE_DIRECTORIES(common/inc)

add_executable(CPP_babel_2018
        server/src/main.cpp
        server/src/TcpClient.cpp
        server/inc/TcpClient.hpp
        server/src/TcpServer.cpp
        server/inc/TcpServer.hpp
        server/src/utils/networkBuffer.cpp
        server/inc/utils/networkBuffer.hpp
        server/inc/Handlers.hpp)

TARGET_LINK_LIBRARIES(CPP_babel_2018
        boost_system)
