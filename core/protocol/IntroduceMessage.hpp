//
// Created by flaviangontier on 10/2/18.
//

#ifndef CPP_BABEL_2018_INTRODUCEMESSAGE_HPP
#define CPP_BABEL_2018_INTRODUCEMESSAGE_HPP

#include <string>
#include <vector>
#include <core/io/BinaryStreamReader.hpp>
#include <core/io/BinaryStreamWriter.hpp>

class IntroduceMessage
{
public:
    //FUNCTIONS
    std::tuple<std::string, std::string, int> unpack(marguerite::io::BinaryStreamReader &reader);
    void pack(marguerite::io::BinaryStreamWriter &writer, const std::string &username, const std::string &host, int port);
};


#endif //CPP_BABEL_2018_INTRODUCEMESSAGE_HPP
