//
// Created by flaviangontier on 10/2/18.
//

#include <string>
#include <core/io/BinaryStreamReader.hpp>
#include <core/io/BinaryStreamWriter.hpp>
#include "Message.hpp"

constexpr int header_size = 11;

void Message::pack(marguerite::io::BinaryStreamWriter &writer, int id)
{
    writer.writeString("BABEL");
    writer.writeInt(id);
}

int Message::unpack(marguerite::io::BinaryStreamReader &reader)
{
    if (reader.getLength() < header_size || reader.readString() != "BABEL")
        return (-1);
    return (reader.readInt());
}
