//
// Created by NANAA on 01/10/18.
//

#ifndef CPP_BABEL_2018_READSERVERWORKER_HPP
#define CPP_BABEL_2018_READSERVERWORKER_HPP

#include <QtCore/QThread>
#include <iostream>
#include <core/net/Socket.hpp>
#include <client/inc/viewmodel/ViewModel.hpp>

class ViewModel;
class Client;

class readServerWorker : public QThread
{
Q_OBJECT
void run() override;

public:
	marguerite::net::Socket *m_socket;
	ViewModel *m_viewModel;
	Client *m_parent;

private:
	void contactReceivedHandler(marguerite::io::BinaryStreamReader &reader);
	void callReceivedHandler(marguerite::io::BinaryStreamReader &reader);
};

#endif //CPP_BABEL_2018_READSERVERWORKER_HPP
