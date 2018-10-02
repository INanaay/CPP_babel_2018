//
// Created by NANAA on 02/10/18.
//

#include <QtCore/QThread>
#include <iostream>
#include <core/net/Socket.hpp>
#include <client/inc/common/contacts.hpp>

#ifndef CPP_BABEL_2018_UDPWORKER_HPP
#define CPP_BABEL_2018_UDPWORKER_HPP

class ViewModel;
class Client;

class udpWorker : public QThread
{
Q_OBJECT
void run() override;
void callContact(const std::string &ip) const;

public:
	ViewModel *m_viewModel;
	Client *m_parent;
	marguerite::net::Socket *m_udpSocket;
	std::vector<Contact> *contacts;
	std::string ip;
	int port;


};

#endif //CPP_BABEL_2018_UDPWORKER_HPP
