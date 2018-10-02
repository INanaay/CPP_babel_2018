//
// Created by flaviangontier on 10/2/18.
//

#include <core/io/BinaryStreamWriter.hpp>
#include <core/io/BinaryStreamReader.hpp>

#include "ListMessage.hpp"

void
ListMessage::pack
(marguerite::io::BinaryStreamWriter &writer, std::vector<std::tuple<std::string, std::string, int>> &contacts)
{
    writer.writeInt(contacts.size());
    for (auto &tuple: contacts)
    {
        writer.writeString(std::get<0>(tuple));
        writer.writeString(std::get<1>(tuple));
        writer.writeInt(std::get<2>(tuple));
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
}
