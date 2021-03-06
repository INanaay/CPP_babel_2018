//
// Created by NANAA on 28/09/18.
//

#ifndef CPP_BABEL_2018_VIEWMODEL_HPP
#define CPP_BABEL_2018_VIEWMODEL_HPP

#include <client/inc/common/contacts.hpp>
#include <client/gui/mainwindow.hpp>
#include <client/gui/loginscreen.hpp>

class MainWindow;
class Client;
class loginScreen;

class ViewModel
{
public:
	ViewModel();
	void startCall(int index) const;
	void start() const;
	void startMainApplication();
	void connectToServer() const;
	void populateContactList() const;
	void setClientUsername(const std::string &username);
	void setIpServer(const std::string &ip);
	void hidePopup() const;
	void showPopup(const std::string &username) const;
	void acceptCall() const;
	void showError() const;
	void changeCallButtons() const;
	void changeHangButton() const;
	void stopCall() const;
private:
	MainWindow *m_mainWindow;
	loginScreen *m_loginScreen;
	Client *m_client;
};

#endif //CPP_BABEL_2018_VIEWMODEL_HPP
