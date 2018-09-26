//
// Created by flaviangontier on 9/26/18.
//

#include <core/net/TcpServer.hpp>

int main(int argc, char **argv)
{
    marguerite::net::TcpServer server("127.0.0.1", 6666);

    server.start();
    return (0);
}