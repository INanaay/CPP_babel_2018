//
// Created by flaviangontier on 10/2/18.
//

#include "AudioMessage.hpp"

void AudioMessage::pack(marguerite::io::BinaryStreamWriter &writer, std::vector<uint8_t> &frame)
{
    writer.writeInt(frame.size());
    writer.writeBytes(frame.data(), frame.size());
}

std::vector<uint8_t> AudioMessage::unpack(marguerite::io::BinaryStreamReader &reader)
{
    int length = reader.readInt();

    std::vector<uint8_t> frame(length);
    reader.readBytes(frame.data(), length);
    return (std::move(frame));
}
