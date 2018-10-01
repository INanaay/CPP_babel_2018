//
// Created by NANAA on 28/09/18.
//


#include <client/inc/viewmodel/ViewModel.hpp>

ViewModel::ViewModel() : m_mainWindow(nullptr)
{
	m_loginScreen = new loginScreen();
	m_client = new Client();

	if (m_client == nullptr || m_loginScreen == nullptr)
		throw std::exception();

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

	m_loginScreen->hide();
	m_mainWindow->show();
	m_mainWindow->setM_viewModel(this);
}

void ViewModel::populateContactList(const std::vector<Contact> &contacts) const
{
	//m_mainWindow->populateContactList();
}

void ViewModel::setClientUsername(const std::string &username)
{
	m_client->setM_username(username);
}

