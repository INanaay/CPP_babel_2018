//
// Created by NANAA on 26/09/18.
//

#ifndef CPP_BABEL_2018_CLIENT_HPP
#define CPP_BABEL_2018_CLIENT_HPP

#include <client/inc/audio/AudioManager.hpp>
#include <client/inc/audio/EncodeManager.hpp>
#include <client/gui/mainwindow.hpp>
#include <core/io/BinaryStreamWriter.hpp>
#include <core/io/BinaryStreamReader.hpp>
#include "client/inc/common/contacts.hpp"
#include "client/inc/client/udpWorker.hpp"
#include "readServerWorker.hpp"

class ViewModel;
class MainWindow;
class readServerWorker;
class udpWorker;

enum Status
{
	INACTIVE,
	ACTIVE,
	RECEIVING_CALL,
	IN_CALL
};

class Client
{
public:
	Client();
	void test();
	void connectToServer();
	void setM_username(const std::string &m_username);
	void getContacts(std::vector<std::tuple<std::string, std::string, int>> &contacts);
	const std::vector<Contact> &getM_contacts() const;
	void startWorker();
	void startUdpWorker();
	void setM_clientStatus(Status m_clientStatus);
	void setM_contacts(const std::vector<Contact> &m_contacts);
	void setM_viewModel(ViewModel *m_viewModel);
	const std::string &getM_username() const;

private:
	readServerWorker *m_worker;
	udpWorker *m_udpWorker;
	AudioManager m_audioManager;
	EncodeManager m_encodeManager;
	std::string m_username;
	Status m_clientStatus;
	MainWindow *mainWindow;
	std::vector<Contact> m_contacts;
	marguerite::net::Socket m_socket;
	marguerite::net::Socket m_udpSocket;
	ViewModel *m_viewModel;

};

#endif //CPP_BABEL_2018_CLIENT_HPP
