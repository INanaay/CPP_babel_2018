//
// Created by NANAA on 26/09/18.
//

#include <client/inc/client/client.hpp>

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

