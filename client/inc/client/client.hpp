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

class MainWindow;

enum Status
{
	INACTIVE,
	RECEIVING_CALL,
	IN_CALL
};

class Client
{

public:


public:
	Client();
	void test();
	void connectToServer();
	void setM_username(const std::string &m_username);
	void getContacts(marguerite::io::BinaryStreamReader &reader);
	const std::vector<Contact> &getM_contacts() const;

private:
	AudioManager m_audioManager;
	EncodeManager m_encodeManager;
	std::string m_username;
	Status m_clientStatus;
	MainWindow *mainWindow;
	std::vector<Contact> m_contacts;
};

#endif //CPP_BABEL_2018_CLIENT_HPP
