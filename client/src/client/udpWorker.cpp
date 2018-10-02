//
// Created by NANAA on 02/10/18.
//

#include <client/inc/client/udpWorker.hpp>
#include <core/protocol/Message.hpp>
#include <core/io/BinaryStreamReader.hpp>
#include "client/inc/client/udpWorker.hpp"

void udpWorker::run()
{
	while (1)
	{
		m_udpSocket->mReceiveFrom(1024, ip, port);
	}
		/*
		auto buffer = m_udpSocket(1024);

		marguerite::io::BinaryStreamReader reader(buffer);

		auto id = Message().unpack(reader);
		 */

}

