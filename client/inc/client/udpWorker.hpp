//
// Created by NANAA on 02/10/18.
//



#ifndef CPP_BABEL_2018_UDPWORKER_HPP
#define CPP_BABEL_2018_UDPWORKER_HPP

#include <QtCore/QThread>
#include <iostream>
#include <core/net/Socket.hpp>
#include "client/inc/common/contacts.hpp"
#include "client.hpp"

class Client;
class ViewModel;

class udpWorker : public QThread
{
Q_OBJECT
void run() override;

public:
	ViewModel *m_viewModel;
	Client *m_parent;
	marguerite::net::Socket *m_udpSocket;
	std::vector<Contact> *contacts;
	std::string ip;
	int port;
	void receiveAudioData(std::vector<uint8_t> &audio);
	void stopCallHandler();

};

#endif //CPP_BABEL_2018_UDPWORKER_HPP
