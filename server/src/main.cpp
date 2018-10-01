//
// Created by flaviangontier on 9/26/18.
//

#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <core/net/TcpServer.hpp>
#include <client/inc/audio/AudioManager.hpp>
#include <client/inc/audio/EncodeManager.hpp>

int main(int argc, char **argv)
{
    marguerite::net::TcpServer auth("0.0.0.0", 6666);

    auth.start();
    return (0);
}