//
// Created by NANAA on 01/10/18.
//

#include <client/inc/client/readServerWorker.hpp>
#include <core/protocol/Message.hpp>
#include <core/protocol/ListMessage.hpp>
#include "client/inc/common/contacts.hpp"

void readServerWorker::run()
{
	while (1) {
		auto buffer = m_socket->mReceive(1024);

		marguerite::io::BinaryStreamReader reader(buffer);

		auto id = Message().unpack(reader);

		switch (id) {
			case 1 :
				contactReceivedHandler(reader);
				break;
		}

	}
}

void readServerWorker::contactReceivedHandler(marguerite::io::BinaryStreamReader &reader)
{
	auto list = ListMessage().unpack(reader);

	std::vector<Contact> contacts;

	for (const auto &contact : list)
	{
		Contact newContact;

		newContact.username = std::get<0>(contact);
		if (m_parent->getM_username() == newContact.username)
			continue;
		newContact.ip = std::get<1>(contact);
		newContact.port = std::get<2>(contact);
		contacts.push_back(newContact);
	}

	m_parent->setM_contacts(contacts);
	std::cout << "Trying to populate List" << std::endl;
	m_viewModel->populateContactList();
}