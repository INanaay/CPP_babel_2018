//
// Created by flaviangontier on 9/19/18.
//

#include "../inc/TcpServer.hpp"
#include "../inc/TcpClient.hpp"
#include <iostream>

TcpServer::TcpServer(const std::string &ip, int port)
: m_endpoint(boost::asio::ip::tcp::v4(), port),
  m_listener(m_ioProvider, m_endpoint),
  m_isRunning(false)
{
}

void TcpServer::accept()
{
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(m_ioProvider);

    auto acceptCallback = [this, socket](const boost::system::error_code &err)
    {
        if (err)
        {
            std::cerr << "error while accepting new connection:" << std::endl;
            std::cerr << err.message() << std::endl;
            return;
        }
        std::cout << "new client accepted." << std::endl;

        auto uid = boost::uuids::random_generator()();
        auto client = std::make_shared<TcpClient>(uid, socket);

        m_clients.insert(std::pair<boost::uuids::uuid, std::shared_ptr<TcpClient>>(uid, client));

        if (this->m_isRunning)
            this->accept();
    };

    m_listener.async_accept(*socket, acceptCallback);
}

void TcpServer::run()
{
    if (m_isRunning)
    {
        std::cerr << "trying to run a server which is already running." << std::endl;
        return;
    }
    m_isRunning = true;

    this->accept();
    m_ioProvider.run();
}