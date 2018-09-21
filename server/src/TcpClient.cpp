//
// Created by flaviangontier on 9/19/18.
//

#include <iostream>
#include <boost/asio.hpp>

#include "../inc/TcpClient.hpp"
#include "../inc/Handlers.hpp"

TcpClient::TcpClient(const boost::uuids::uuid &uid, const std::shared_ptr<boost::asio::ip::tcp::socket> &socket)
: m_uid(uid), m_socket(socket)
{
    receive();
}

void TcpClient::disconnect()
{

}

void TcpClient::parse(const char *buffer, std::size_t length)
{
    m_buffer.append(buffer, length);

    std::uint16_t packet_id = 0;
    memcpy(&packet_id, buffer, sizeof(std::uint16_t));
    std::size_t packet_length = 0;
    memcpy(&packet_length, buffer + sizeof(std::uint16_t), sizeof(std::size_t));

    if (packet_length > m_buffer.size())
        return;

    switch (packet_id)
    {
        case 0:
        {
            IntroduceHandler(this, buffer + sizeof(std::uint16_t) + sizeof(std::size_t));
            break;
        }
        default:
        {
            std::cerr << "unknow packet received." << std::endl;
        }
    }
}

void TcpClient::receive()
{
    char data[256];
    auto buffer = boost::asio::buffer(data, sizeof(data));

    auto receiveCallback = [this, buffer](const boost::system::error_code& error, std::size_t length)
    {
        if (error)
        {
            std::cerr << "error while receiving data:" << error.message() << std::endl;
            return;
        }
        if (length == 0)
        {
            this->disconnect();
            return;
        }

        const char *packet = boost::asio::buffer_cast<char *>(buffer);
        this->parse(packet, length);
        this->receive();
    };
    m_socket->async_receive(buffer, 0, receiveCallback);
}

const boost::uuids::uuid &TcpClient::getUid() const
{
    return (m_uid);
}

const std::shared_ptr<boost::asio::ip::tcp::socket> &TcpClient::getSocket() const
{
    return (m_socket);
}

void TcpClient::setUsername(const std::string &name)
{
    m_username = name;
}
