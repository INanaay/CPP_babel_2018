//
// Created by flaviangontier on 10/2/18.
//

#ifndef CPP_BABEL_2018_MESSAGE_HPP
#define CPP_BABEL_2018_MESSAGE_HPP


#include <vector>
#include <cstdint>

class Message
{
public:
    int unpack(marguerite::io::BinaryStreamReader &reader);
    void pack(marguerite::io::BinaryStreamWriter &writer, int id);
};


#endif //CPP_BABEL_2018_MESSAGE_HPP
