//
// Created by flaviangontier on 10/2/18.
//

#ifndef CPP_BABEL_2018_AUDIOMESSAGE_HPP
#define CPP_BABEL_2018_AUDIOMESSAGE_HPP


#include <core/io/BinaryStreamWriter.hpp>
#include <core/io/BinaryStreamReader.hpp>

class AudioMessage
{
    static void pack(marguerite::io::BinaryStreamWriter &writer, std::vector<uint8_t> &frame);
    static std::vector<uint8_t> unpack(marguerite::io::BinaryStreamReader &reader);
};


#endif //CPP_BABEL_2018_AUDIOMESSAGE_HPP
