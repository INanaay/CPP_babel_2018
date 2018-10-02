//
// Created by flaviangontier on 10/2/18.
//

#ifndef CPP_BABEL_2018_MESSAGE_HPP
#define CPP_BABEL_2018_MESSAGE_HPP

#include <vector>
#include <cstdint>
#include "core/io/BinaryStream.hpp"
#include "core/io/BinaryStreamReader.hpp"
#include "core/io/BinaryStreamWriter.hpp"

class Message
{
public:
    static int unpack(marguerite::io::BinaryStreamReader &reader);
    static void pack(marguerite::io::BinaryStreamWriter &writer, int id);
};


#endif //CPP_BABEL_2018_MESSAGE_HPP
