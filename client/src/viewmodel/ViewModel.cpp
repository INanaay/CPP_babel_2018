//
// Created by NANAA on 28/09/18.
//


#include <client/inc/viewmodel/ViewModel.hpp>
#include <thread>

ViewModel::ViewModel() : m_mainWindow(nullptr)
{
	m_loginScreen = new loginScreen();
	m_client = new Client();

	if (m_client == nullptr || m_loginScreen == nullptr)
		throw std::exception();

	m_client->setM_viewModel(this);
	m_loginScreen->setM_viewModel(this);
}

void ViewModel::start() const
{
	m_loginScreen->show();
}

void ViewModel::startMainApplication()
{
	m_mainWindow = new MainWindow();

	if (m_mainWindow == nullptr)
		throw std::exception();

	m_mainWindow->setM_viewModel(this);
	populateContactList();
	//m_mainWindow->populateContactList(m_client->getM_contacts());
	m_loginScreen->hide();
	m_mainWindow->show();
	m_client->startWorker();
	m_client->startUdpWorker();

}


void ViewModel::setClientUsername(const std::string &username)
{
	m_client->setM_username(username);
}

void ViewModel::connectToServer() const
{
	m_client->connectToServer();
}

void ViewModel::populateContactList() const
{
	m_mainWindow->populateContactList(m_client->getM_contacts());

}

void ViewModel::startCall(int index) const
{
	m_client->startCall(index);
}


