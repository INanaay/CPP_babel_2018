/*
** EPITECH PROJECT, 2018
** Epitech scolarship project (4 years remaining)
** File description:
**      Made on 2018/05 by lebovin
*/

#include <unistd.h>
#include <stdexcept>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <asm/ioctls.h>
#include <sys/ioctl.h>
#include <memory>
#include <iostream>
#include <cstring>
#include "Socket.hpp"

marguerite::net::Socket::Socket(int sockfd, const sockaddr_in &addr, IpType iptype, ProtocolType prototype)
: m_sockfd(sockfd), m_connected(true), m_listening(false), m_port(ntohs(addr.sin_port)), m_protocol(prototype)
{
    char ip[INET6_ADDRSTRLEN];
    switch (addr.sin_family)
    {
        case AF_INET:
            m_ipType = IpType::V4;
            inet_ntop(AF_INET, &(addr.sin_addr), ip, INET_ADDRSTRLEN);
            m_host = std::string(ip, INET_ADDRSTRLEN);
            break;
        case AF_INET6:
            m_ipType = IpType::V6;
            inet_ntop(AF_INET6, &(addr.sin_addr), ip, INET6_ADDRSTRLEN);
            m_host = std::string(ip, INET6_ADDRSTRLEN);
            break;
    }
    m_listening = false;
}

marguerite::net::Socket::Socket(IpType ip_type, ProtocolType protocol_type)
: Socket((int)ip_type, (int)protocol_type)
{ }

marguerite::net::Socket::Socket(int ip_type, int protocol_type)
: m_binded(false),
  m_listening(false),
  m_connected(false)
{

#ifdef _WIN32
	WSADATA wsa;
	SOCKET sock;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		std::runtime_error("cannot start winsock.");
#endif

	m_ipType = (IpType)ip_type;
	m_protocol = (ProtocolType)protocol_type;

	m_sockfd = socket(ip_type, protocol_type, 0);
	if (m_sockfd == -1)
		throw std::runtime_error("cannot create socket.");

	sockaddr_in addr;
	socklen_t addr_size = sizeof(sockaddr_in);

	getpeername(m_sockfd, (sockaddr *)&addr, &addr_size);
    m_port = ntohs(addr.sin_port);
	m_host = std::string(inet_ntoa(addr.sin_addr));
}

marguerite::net::Socket::~Socket()
{
	if (m_sockfd != -1)
		close(m_sockfd);
}


void marguerite::net::Socket::mBind(const std::string &host, int port)
{
	int optname = 1;
	if (setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optname, sizeof(optname)) == -1)
		throw std::runtime_error("cannot re-use address or port.");

	sockaddr_in laddr;
	laddr.sin_family = AF_INET;
	laddr.sin_addr.s_addr = inet_addr(host.c_str());
	laddr.sin_port = htons(port);

	if (bind(m_sockfd, (sockaddr *)&laddr, sizeof(laddr)) == -1)
		throw std::runtime_error("cannot bind the socket.");

	m_binded = true;
}

std::shared_ptr<marguerite::net::Socket> marguerite::net::Socket::mAccept()
{
    if (m_protocol != ProtocolType::TCP)
        throw std::runtime_error("trying to accept tcp connection with udp socket.");
	if (!m_binded || !m_listening)
		throw std::runtime_error("trying to accept incoming connection on unbinded or non-listening socket.");

	sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	int sockfd = accept(m_sockfd, (sockaddr *)&addr, &addrlen);

	if (sockfd == -1)
		throw std::runtime_error("accepting incoming connection failed.");

	auto client = std::make_shared<Socket>(sockfd, addr, IpType::V4, ProtocolType::TCP);
	return (client);
}

void marguerite::net::Socket::mListen(std::size_t capacity)
{
	if (!m_binded)
		throw std::runtime_error("try to listen on unbinded socket.");

	if (listen(m_sockfd, capacity) == -1)
		throw std::runtime_error("cannot listen on given socket.");

	m_listening = true;
	m_connected = true;
}

void marguerite::net::Socket::mConnect(const std::string &host, int port)
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(host.c_str());
	addr.sin_port = htons(port);

	if (connect(m_sockfd, (sockaddr *)&addr, sizeof(addr)) == -1)
		throw std::runtime_error("cannot connect to given remote addr/port.");

	m_connected = true;
}
int marguerite::net::Socket::available() const
{
	if (!m_connected && m_protocol == ProtocolType::TCP)
		return 0;

	int amount;
	if (ioctl(m_sockfd, FIONREAD, &amount) == -1)
		throw std::runtime_error("cannot get amount of available data on the socket.");

	return (amount);
}

std::vector<uint8_t> marguerite::net::Socket::mReceive(std::size_t amount)
{
    auto ret = std::vector<uint8_t>(amount);

    read(m_sockfd, ret.data(), amount);
    return (std::move(ret));
}

void marguerite::net::Socket::mReceive(uint8_t *dest, std::size_t amount)
{
    read(m_sockfd, dest, amount);
}

std::vector<uint8_t> marguerite::net::Socket::mReceiveFrom(std::size_t amount, sockaddr_in &addr)
{
    socklen_t len = sizeof(addr);
    auto ret = std::vector<uint8_t>(amount);

    recvfrom(m_sockfd, ret.data(), amount, 0, ((sockaddr *)&addr), &len);
    return std::move(ret);
}

std::vector<uint8_t> marguerite::net::Socket::mReceiveFrom(std::size_t amount, const std::string &host, int port)
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(host.c_str());
	addr.sin_port = htons(port);

	return mReceiveFrom(amount, addr);
}

void marguerite::net::Socket::mSend(const std::vector<uint8_t> &buffer)
{
    write(m_sockfd, buffer.data(), buffer.size());
}

void marguerite::net::Socket::mSend(const uint8_t *buffer, std::size_t n)
{
    write(m_sockfd, buffer, n);
}

void marguerite::net::Socket::mSendTo(std::vector<uint8_t> &buffer, std::size_t amount, const std::string &host, int port)
{
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(host.c_str());
	addr.sin_port = htons(port);

	sendto(m_sockfd, buffer.data(), amount, 0, (sockaddr *)&addr, sizeof(addr));
}

int marguerite::net::Socket::getSockfd() const
{
    return m_sockfd;
}

int marguerite::net::Socket::getPort() const
{
	return m_port;
}

std::string marguerite::net::Socket::getHost() const
{
	return m_host;
}
