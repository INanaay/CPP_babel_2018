//
// Created by NANAA on 02/10/18.
//

#include <client/inc/client/udpWorker.hpp>
#include <core/protocol/Message.hpp>
#include <core/io/BinaryStreamReader.hpp>
#include <core/protocol/AudioMessage.hpp>
#include "client/inc/client/udpWorker.hpp"

void udpWorker::run()
{
	std::cout << "STARTED UDP WORKER" << std::endl << std::endl;
	while (1)
	{

		auto buffer = m_udpSocket->mReceiveFrom(1024, ip, port);

		marguerite::io::BinaryStreamReader reader(buffer);

		//std::cout << "Received data in udp" << std::endl;

		auto id = Message::unpack(reader);

		if (id == 4)
		{
			std::cout << "Stoping call" << std::endl;
			stopCallHandler();

		}

		auto audio = AudioMessage::unpack(reader);
		receiveAudioData(audio);
	}
}

void udpWorker::receiveAudioData(std::vector<uint8_t> &audio)
{
	m_parent->decodeData(audio);
}

void udpWorker::stopCallHandler()
{
	m_parent->stopCall();
}
