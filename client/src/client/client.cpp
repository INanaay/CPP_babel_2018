//
// Created by NANAA on 26/09/18.
//

#include <client/inc/client/client.hpp>
#include <core/net/Socket.hpp>
#include <cstring>
#include <thread>
#include <unistd.h>


Client::Client() : m_audioManager(), m_encodeManager(), m_clientStatus(INACTIVE)
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

	marguerite::io::BinaryStreamWriter writer;
	writer.writeString("BABEL");
	writer.writeInt(0);
	writer.writeInt(m_username.size());
	writer.writeString(m_username);

	socket.mSend(writer.getBuffer());
	auto buffer = socket.mReceive(1024);


	marguerite::io::BinaryStreamReader reader(buffer);
	std::cout << "Reader declared" << std::endl;

	std::cout << reader.readString() << std::endl;
	std::cout << reader.readInt() << std::endl;
	getContacts(reader);
}

void Client::getContacts(marguerite::io::BinaryStreamReader &reader)
{
	auto bodyOffset = reader.readInt() + reader.getOffset();
	Contact newContact;

	while (reader.getOffset() < bodyOffset)
	{
		newContact.username = reader.readString();
		newContact.ip = reader.readString();
		newContact.port = reader.readInt();

		m_contacts.push_back(newContact);
	}

}

const std::vector<Contact> &Client::getM_contacts() const {
	return m_contacts;
}


void Client::setM_clientStatus(Status m_clientStatus) {
	Client::m_clientStatus = m_clientStatus;
}

void Client::startWorker()
{
	m_worker = new readServerWorker();
	m_worker->start();
}



