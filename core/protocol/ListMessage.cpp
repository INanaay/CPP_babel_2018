//
// Created by flaviangontier on 10/2/18.
//

#include <core/io/BinaryStreamWriter.hpp>
#include <core/io/BinaryStreamReader.hpp>
#include <core/net/TcpServer.hpp>

#include "ListMessage.hpp"

void
ListMessage::pack
(marguerite::io::BinaryStreamWriter &writer, const std::unordered_map<int, marguerite::net::User> &users)
{
    writer.writeInt((int)users.size());
    for (auto &pair: users)
    {
        auto user = pair.second;

        writer.writeString(user.username);
        writer.writeString(user.udpHost);
        writer.writeInt(user.udpPort);
    }
}

std::vector<std::tuple<std::string, std::string, int>>
ListMessage::unpack
(marguerite::io::BinaryStreamReader &reader)
{
    std::vector<std::tuple<std::string, std::string, int>> contacts;

    int count = reader.readInt();
    for (int i = 0; i < count; i++)
        contacts.push_back({reader.readString(), reader.readString(), reader.readInt()});

    return (std::move(contacts));
}
