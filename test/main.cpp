//
// Created by flaviangontier on 10/1/18.
//

#include <core/net/Socket.hpp>
#include <core/io/BinaryStreamWriter.hpp>
#include <core/io/BinaryStreamReader.hpp>
#include <iostream>

int main()
{
    marguerite::net::Socket socket(marguerite::net::IpType::V4, marguerite::net::ProtocolType::TCP);
    socket.mConnect("127.0.0.1", 6666);

    marguerite::io::BinaryStreamWriter writer;
    writer.writeString("BABEL");
    writer.writeInt(0);
    writer.writeInt(5);
    writer.writeString("ABC");

    socket.mSend(writer.getBuffer());
    auto buffer = socket.mReceive(socket.available());

    marguerite::io::BinaryStreamReader reader(buffer);
    std::cout << reader.readString() << std::endl;
    std::cout << reader.readInt() << std::endl;
    auto bodyOffset = reader.readInt() + reader.getOffset();
    std::cout << bodyOffset << std::endl;

    while (reader.getOffset() < bodyOffset)
    {
        std::cout << reader.readString() << std::endl;
        std::cout << reader.readString() << std::endl;
        std::cout << reader.readInt() << std::endl;
    }
}

