//
// Created by flaviangontier on 10/2/18.
//

#include "IntroduceMessage.hpp"
void
IntroduceMessage::pack
(marguerite::io::BinaryStreamWriter &writer, const std::string &username, const std::string &host, int port)
{
    writer.writeString(username);
    writer.writeString(host);
    writer.writeInt(port);
}

std::tuple<std::string, std::string, int>
IntroduceMessage::unpack
(marguerite::io::BinaryStreamReader &reader)
{
    std::tuple<std::string, std::string, int> ret;

    std::get<0>(ret) = reader.readString();
    std::get<1>(ret) = reader.readString();
    std::get<2>(ret) = reader.readInt();
    return (std::move(ret));
}
