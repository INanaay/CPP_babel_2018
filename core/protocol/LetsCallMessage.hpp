//
// Created by flaviangontier on 10/2/18.
//

#ifndef CPP_BABEL_2018_LETSCALL_HPP
#define CPP_BABEL_2018_LETSCALL_HPP


#include <core/io/BinaryStreamWriter.hpp>
#include <core/io/BinaryStreamReader.hpp>

class LetsCallMessage
{
public:
    static void pack(marguerite::io::BinaryStreamWriter &writer, const std::string &username);
    static std::string unpack(marguerite::io::BinaryStreamReader &writer);
};


#endif //CPP_BABEL_2018_LETSCALL_HPP
