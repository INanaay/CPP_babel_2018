//
// Created by NANAA on 26/09/18.
//

#include <client/inc/client/client.hpp>
#include <core/net/Socket.hpp>
#include <cstring>
#include <thread>
#include <unistd.h>
#include <core/protocol/IntroduceMessage.hpp>
#include <core/protocol/Message.hpp>
#include <core/protocol/ListMessage.hpp>
#include <core/protocol/LetsCallMessage.hpp>
#include <ctime>

Client::Client() : m_audioManager(), m_encodeManager(), m_clientStatus(INACTIVE), m_socket(marguerite::net::IpType::V4,
	marguerite::net::ProtocolType::TCP), m_viewModel(nullptr), m_udpWorker(nullptr), m_udpSocket(marguerite::net::IpType::V4,
												     marguerite::net::ProtocolType::UDP)
{
	std::cout << "Creating client" << std::endl;
	m_udpSocket.mBind("0.0.0.0", 4444);

}

void Client::test() {
	std::cout << "Yo this is a test" << std::endl;
}

void Client::setM_username(const std::string &m_username) {
	Client::m_username = m_username;
}



void Client::connectToServer()
{

	std::cout << "Trying to connect" << std::endl;

	//m_socket.mConnect("127.0.0.1", 6666);

	m_socket.mConnect(m_serverIp, 6666);
	marguerite::io::BinaryStreamWriter writer;

	Message::pack(writer, 0);
	IntroduceMessage().pack(writer, m_username, m_udpSocket.getHost(), m_udpSocket.getPort());

	m_socket.mSend(writer.getBuffer());
	auto buffer = m_socket.mReceive(1024);

	marguerite::io::BinaryStreamReader reader(buffer);
	Message::unpack(reader);
	auto list = ListMessage::unpack(reader);
	getContacts(list);
/*
	marguerite::io::BinaryStreamReader reader(buffer);
	std::cout << reader.readString() << std::endl;
	std::cout << reader.readInt() << std::endl;
	getContacts(reader); */
}

void Client::getContacts(std::vector<std::tuple<std::string, std::string, int>> &contacts)
{
	m_contacts.clear();
	for (auto &contact: contacts) {

		if (m_username == std::get<0>(contact))
			continue;
		m_contacts.push_back({std::get<0>(contact), std::get<1>(contact), std::get<2>(contact)});
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
	m_worker->m_socket = &m_socket;
	m_worker->m_parent = this;
	m_worker->m_viewModel = m_viewModel;
	m_worker->start();
}

void Client::setM_contacts(const std::vector<Contact> &m_contacts) {
	Client::m_contacts = m_contacts;
}

void Client::setM_viewModel(ViewModel *m_viewModel) {
	Client::m_viewModel = m_viewModel;
}

const std::string &Client::getM_username() const {
	return m_username;
}

void Client::startUdpWorker()
{
	m_udpWorker = new udpWorker();
	m_udpWorker->m_parent = this;
	m_udpWorker->contacts = &m_contacts;
	m_udpWorker->m_viewModel = m_viewModel;
	m_udpWorker->m_udpSocket = &m_udpSocket;
}

void Client::tryToCall(int index)
{
	auto contact = m_contacts[index];
	marguerite::io::BinaryStreamWriter writer;

	std::cout << "Trying to call " << contact.username << std::endl;

	Message::pack(writer, 2);
	LetsCallMessage::pack(writer, contact.username);
	m_socket.mSend(writer.getBuffer());
	m_udpWorker->port = contact.port;
	m_udpWorker->ip = contact.ip;
	m_udpWorker->start();

	m_audioManager.startAudioRecording();

	while (1)
	{
		auto sample = m_audioManager.getLastRecord();

		if (sample.size > 0)
		{
			auto encodedData = m_encodeManager.encode(sample);
			m_udpSocket.mSendTo(encodedData.audio, encodedData.size, contact.ip, contact.port);
		}
	}
}

void Client::setM_serverIp(const std::string &m_serverIp) {
	Client::m_serverIp = m_serverIp;
}

void Client::callReceived(const std::string &username)
{

	clock_t start = clock();

	m_currentCaller = username;
	m_viewModel->showPopup(username);
	while (((double) clock() - start) / CLOCKS_PER_SEC < 5);
	m_viewModel->hidePopup();
}

void Client::acceptCall()
{
	std::cout << "accepting call" << std::endl;
	std::vector<uint8_t > buffer;
	Contact caller;

	buffer.push_back('l');
	buffer.push_back('l');

	for (const auto &contact : m_contacts)
	{
		if (contact.username == m_currentCaller)
		{
			std::cout << "ip:" << contact.ip << std::endl;
			std::cout << "port: " << contact.port << std::endl;
			caller = contact;
			break;
		}
	}

	m_udpWorker->port = caller.port;
	m_udpWorker->ip = caller.ip;
	m_udpWorker->start();
	m_udpSocket.mSendTo(buffer, 2, caller.ip, caller.port);


	m_viewModel->hidePopup();
}



