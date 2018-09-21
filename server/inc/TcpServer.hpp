//
// Created by flaviangontier on 9/19/18.
//

#ifndef CPP_BABEL_2018_TCPSERVER_HPP
#define CPP_BABEL_2018_TCPSERVER_HPP

#include <string>
#include <boost/asio.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

class TcpClient;

class TcpServer
{
public:
    //CTOR DTOR
    explicit TcpServer(const std::string &ip = "127.0.0.1", int port = 6666);

    //FUNCTIONS
    void run();

private:
    bool m_isRunning;

    boost::asio::io_service m_ioProvider;
    boost::asio::ip::tcp::endpoint m_endpoint;
    boost::asio::ip::tcp::acceptor m_listener;

    std::map<boost::uuids::uuid, std::shared_ptr<TcpClient>> m_clients;

    void accept();
    void receive(std::shared_ptr<TcpClient> client, std::shared_ptr<boost::asio::ip::tcp::socket> socket);
};


#endif //CPP_BABEL_2018_TCPSERVER_HPP
