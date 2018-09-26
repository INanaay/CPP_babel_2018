cmake_minimum_required(VERSION 3.9)
project(CPP_babel_2018)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-lpthread -fPIC")

if(EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()
else()
    message(WARNING "The file conanbuildinfo.cmake doesn't exist, you have to run conan install first")
endif()


LINK_DIRECTORIES(deps/libs)
INCLUDE_DIRECTORIES(deps/incs)

add_executable(CPP_babel_server
        server/src/main.cpp
        server/src/TcpClient.cpp
        server/inc/TcpClient.hpp
        server/src/TcpServer.cpp
        server/inc/TcpServer.hpp
        server/src/utils/networkBuffer.cpp
        server/inc/utils/networkBuffer.hpp
        server/inc/Handlers.hpp)

TARGET_LINK_LIBRARIES(CPP_babel_server
        boost_system)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5OpenGL CONFIG REQUIRED)
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)

add_executable(CPP_babel_client
        client/src/main.cpp
        client/src/audio/AudioManager.cpp
        client/src/audio/EncodeManager.cpp client/src/network/TcpClient.cpp client/inc/network/TcpClient.hpp
        client/gui/loginscreen.cpp client/gui/loginscreen.hpp
        client/gui/mainwindow.hpp client/gui/mainwindow.cpp
        client/src/client/client.cpp client/inc/client/client.hpp
        )

target_link_libraries(CPP_babel_client
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        Qt5::OpenGL
        ${CONAN_LIBS})
