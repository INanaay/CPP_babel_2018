//
// Created by flaviangontier on 9/26/18.
//

#include <iostream>
#include <sys/epoll.h>
#include <cstring>
#include <core/io/BinaryStreamWriter.hpp>
#include <core/io/BinaryStreamReader.hpp>
#include "TcpServer.hpp"

marguerite::net::TcpServer::TcpServer(const std::string &host, int port, std::size_t max)
: m_listener(IpType::V4, ProtocolType::TCP), m_max(max)
{
    try
    {
        m_listener.mBind(host, port);
        m_listener.mListen(max);
    }
    catch (std::exception &ex)
    {
        std::cerr << "cannot setup the server listener. error:" << ex.what() << std::endl;
    }

    m_epollfd = epoll_create(max);
    if (m_epollfd == -1)
        throw std::runtime_error("cannot create epoll queue.");

    epoll_event evt;
    evt.events = EPOLLIN;
    evt.data.fd = m_listener.getSockfd();

    if (epoll_ctl(m_epollfd, EPOLL_CTL_ADD, evt.data.fd, &evt) == -1)
        throw std::runtime_error("cannot add listener socket to epoll.");
}

marguerite::net::TcpServer::~TcpServer()
{
}

void marguerite::net::TcpServer::stop()
{
    m_running = false;
}

void marguerite::net::TcpServer::start()
{
    epoll_event events[m_max];
    int listenerfd = m_listener.getSockfd();

    m_running = true;
    while (m_running)
    {
        int fds = epoll_wait(m_epollfd, events, m_max, -1);
        if (fds == -1)
            throw std::runtime_error("cannot check incoming activity.");

        for (int index = 0; index < fds; index++)
        {
            int sockfd = events[index].data.fd;
            if (sockfd == listenerfd)
            {
                auto client = m_listener.mAccept();
                int newfd = client->getSockfd();

                epoll_event evt;
                evt.data.fd = newfd;
                evt.events = EPOLLIN;
                epoll_ctl(m_epollfd, EPOLL_CTL_ADD, newfd, &evt);

                m_clients.insert({newfd, client});
                onClientAccepted(client);
            }
            else
            {
                auto client = m_clients[sockfd];
                auto amount = client->available();
                if (amount == 0)
                {
                    epoll_event evt;
                    evt.events = EPOLLIN;
                    evt.data.fd = sockfd;
                    if (epoll_ctl(m_epollfd, EPOLL_CTL_DEL, sockfd, &evt) == -1)
                        throw std::runtime_error("cannot remove fd from epoll.");
                    m_clients.erase(sockfd);

                    onClientDisconnected(client);
                }
                else
                {
                    auto message = client->mReceive(amount);
                    onMessageReceived(client, std::move(message));
                }
            }
        }
    }
}


void marguerite::net::TcpServer::onClientDisconnected(std::shared_ptr<marguerite::net::Socket> socket)
{
    std::cout << "client disconnected." << std::endl;
}

void marguerite::net::TcpServer::onClientAccepted(std::shared_ptr<Socket> socket)
{
    m_buffers.insert({socket->getSockfd(), std::vector<uint8_t>(512)});

    std::cout << "client connected." << std::endl;
}

void marguerite::net::TcpServer::onMessageReceived(std::shared_ptr<Socket> socket, std::vector<uint8_t> message)
{
    std::vector<uint8_t> &buffer = m_buffers[socket->getSockfd()];
    buffer.insert(buffer.begin(), std::make_move_iterator(message.begin()), std::make_move_iterator(message.end()));

    std::cout << "starting to read received message." << std::endl;
    marguerite::io::BinaryStreamReader reader(buffer);

    auto magic = reader.readString();
    if (magic != "BABEL")
        return;

    auto id = reader.readInt();
    auto length = reader.readInt();
    auto remaining = reader.getLength() - reader.getOffset();

    if (length > remaining)
        return;

    switch (id)
    {
        case 0:
            IntroduceHandler(socket, reader);
            buffer.erase(buffer.begin(), buffer.begin() + reader.getOffset());
            break;
    }
}

std::vector<std::tuple<std::string, std::string, int>> marguerite::net::TcpServer::getClientList()
{
    std::vector<std::tuple<std::string, std::string, int>> ret;

    for (auto &pair: m_clients)
    {
        auto fd = pair.first;
        auto sock = m_clients[fd];
        auto username = m_usernames[fd];

        ret.push_back(std::make_tuple(username, sock->getHost(), sock->getPort()));
    }

    return (std::move(ret));
}

void marguerite::net::TcpServer::IntroduceHandler(std::shared_ptr<marguerite::net::Socket> socket, marguerite::io::BinaryStreamReader &reader)
{
    std::cout << "introduce handler." << std::endl;
    m_usernames[socket->getSockfd()] = reader.readString();

    marguerite::io::BinaryStreamWriter bodyWriter;
    marguerite::io::BinaryStreamWriter headerWriter;

    headerWriter.writeString("BABEL");
    headerWriter.writeInt(1);

    auto list = getClientList();
    for (auto &tuple: list)
    {
        bodyWriter.writeString(std::get<0>(tuple));
        bodyWriter.writeString(std::get<1>(tuple));
        bodyWriter.writeInt(std::get<2>(tuple));
    }
    headerWriter.writeInt(bodyWriter.getLength());

    auto header = headerWriter.getBuffer();
    auto body = bodyWriter.getBuffer();
    std::vector<uint8_t> buffer;
    buffer.insert(buffer.begin(), std::make_move_iterator(header.begin()), std::make_move_iterator(header.end()));
    buffer.insert(buffer.end(), std::make_move_iterator(body.begin()), std::make_move_iterator(body.end()));

    socket->mSend(buffer);
}