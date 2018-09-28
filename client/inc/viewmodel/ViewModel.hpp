//
// Created by NANAA on 28/09/18.
//

#ifndef CPP_BABEL_2018_VIEWMODEL_HPP
#define CPP_BABEL_2018_VIEWMODEL_HPP

#include <client/gui/mainwindow.hpp>
#include <client/gui/loginscreen.hpp>

class MainWindow;
class Client;
class loginScreen;

class ViewModel
{
public:
	ViewModel();
	void start();
	void startMainApplication();
private:
	MainWindow *m_mainWindow;
	loginScreen *m_loginScreen;
	Client *m_client;
};

#endif //CPP_BABEL_2018_VIEWMODEL_HPP
