//
// Created by flaviangontier on 10/2/18.
//

#include "LetsCall.hpp"

void LetsCall::pack(marguerite::io::BinaryStreamWriter &writer, const std::string &username)
{
    writer.writeString(username);
}

std::string LetsCall::unpack(marguerite::io::BinaryStreamReader &reader)
{
    std::string ret = reader.readString();
    return (std::move(ret));
}
