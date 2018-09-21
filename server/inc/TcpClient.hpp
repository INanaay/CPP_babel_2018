//
// Created by flaviangontier on 9/19/18.
//

#ifndef CPP_BABEL_2018_TCPCLIENT_HPP
#define CPP_BABEL_2018_TCPCLIENT_HPP

#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include "./utils/networkBuffer.hpp"

class TcpClient
{
public:
    TcpClient(const boost::uuids::uuid &uid, const std::shared_ptr<boost::asio::ip::tcp::socket> &socket);

    //PROPERTIES
    const boost::uuids::uuid &getUid() const;
    const std::shared_ptr<boost::asio::ip::tcp::socket> &getSocket() const;

    //SETTERS
    void setUsername(const std::string &username);

private:
    //NETWORK
    networkBuffer m_buffer;
    boost::uuids::uuid m_uid;
    std::shared_ptr<boost::asio::ip::tcp::socket> m_socket;

    //FIELDS
    std::string m_username;

    //FUNCTIONS
    void parse(const char *buffer, std::size_t length);
    void receive();
    void disconnect();
};


#endif //CPP_BABEL_2018_TCPCLIENT_HPP
