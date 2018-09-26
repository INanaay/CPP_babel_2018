//
// Created by NANAA on 26/09/18.
//

#ifndef CPP_BABEL_2018_CLIENT_HPP
#define CPP_BABEL_2018_CLIENT_HPP

#include <client/inc/audio/AudioManager.hpp>
#include <client/inc/audio/EncodeManager.hpp>

class Client
{
public:
	Client();
	void test();
private:
	AudioManager m_audioManager;
	EncodeManager m_encodeManager;
	std::string m_username;
public:
	void setM_username(const std::string &m_username);
};

#endif //CPP_BABEL_2018_CLIENT_HPP
