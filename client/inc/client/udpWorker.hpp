//
// Created by NANAA on 02/10/18.
//

#include <QtCore/QThread>
#include <iostream>
#include <core/net/Socket.hpp>

#ifndef CPP_BABEL_2018_UDPWORKER_HPP
#define CPP_BABEL_2018_UDPWORKER_HPP

class ViewModel;
class Client;

class udpWorker : public QThread
{
Q_OBJECT
void run() override;

public:
	ViewModel *m_viewModel;
	Client *m_parent;
	marguerite::net::Socket *m_udpSocket;


};

#endif //CPP_BABEL_2018_UDPWORKER_HPP
