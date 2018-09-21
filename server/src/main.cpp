//
// Created by flaviangontier on 9/18/18.
//

#include <iostream>
#include <boost/asio.hpp>
#include "../inc/TcpServer.hpp"

void test_socket()
{
    TcpServer server;

    server.run();
}

int main()
{
    std::cout << "starting server" << std::endl;
    test_socket();
    return (0);
}

