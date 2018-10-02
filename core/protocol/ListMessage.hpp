//
// Created by flaviangontier on 10/2/18.
//

#ifndef CPP_BABEL_2018_LISTMESSAGE_HPP
#define CPP_BABEL_2018_LISTMESSAGE_HPP

#include <core/io/BinaryStreamReader.hpp>
#include <core/io/BinaryStreamWriter.hpp>
#include <core/net/TcpServer.hpp>

class ListMessage
{
public:
    //FUNCTIONS
    static std::vector<std::tuple<std::string, std::string, int>> unpack(marguerite::io::BinaryStreamReader &reader);
    static void pack(marguerite::io::BinaryStreamWriter &writer, const std::unordered_map<int, marguerite::net::User> &contacts);
};


#endif //CPP_BABEL_2018_LISTMESSAGE_HPP
