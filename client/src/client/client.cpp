//
// Created by NANAA on 26/09/18.
//

#include <client/inc/client/client.hpp>
#include <core/net/Socket.hpp>
#include <cstring>

Client::Client() : m_audioManager(), m_encodeManager()
{
	std::cout << "Creating client" << std::endl;

}

void Client::test() {
	std::cout << "Yo this is a test" << std::endl;
}

void Client::setM_username(const std::string &m_username) {
	Client::m_username = m_username;
}

void Client::connectToServer()
{
	marguerite::net::Socket socket(marguerite::net::IpType::V4, marguerite::net::ProtocolType::TCP);

	std::cout << "Trying to connect" << std::endl;
	socket.mConnect("192.168.0.104", 6666);
	socket.mSend((uint8_t *)"hello world!", strlen("hello world!"));
}

