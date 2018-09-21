//
// Created by flaviangontier on 9/21/18.
//

#ifndef CPP_BABEL_2018_HANDLERS_HPP
#define CPP_BABEL_2018_HANDLERS_HPP

#include <cstdio>
#include "TcpClient.hpp"

void IntroduceHandler(TcpClient *client, const char *buffer)
{
    std::size_t username_length = 0;
    memcpy(&username_length, buffer, sizeof(std::size_t));

    std::string username(buffer + sizeof(std::size_t), username_length);

    client->setUsername(username);
}

#endif //CPP_BABEL_2018_HANDLERS_HPP
