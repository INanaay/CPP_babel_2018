//
// Created by flaviangontier on 9/24/18.
//

#ifndef CPP_BABEL_2018_TCPCLIENT_HPP
#define CPP_BABEL_2018_TCPCLIENT_HPP


#include <string>
#include <boost/asio/ip/tcp.hpp>

class TcpClient
{
public:
    TcpClient();
    void connect(const std::string &addr, int port);
    void send(const char *buffer, std::size_t length);
    void disconnect();
private:
    bool connected;
    std::shared_ptr<boost::asio::ip::tcp::socket> m_socket;
};


#endif //CPP_BABEL_2018_TCPCLIENT_HPP
