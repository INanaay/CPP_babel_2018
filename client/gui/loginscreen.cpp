#include <iostream>
#include "loginscreen.hpp"
#include "ui_loginscreen.h"
#include <boost/algorithm/string.hpp>
#include <QDesktopWidget>
#include <QRect>



loginScreen::loginScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginScreen)
{
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);
    setWindowTitle("Login");
    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x()-width() * 0.5, center.y()-height() * 0.5);
    connect(ui->usernameTextBox, SIGNAL(returnPressed()), ui->connect_button, SIGNAL(clicked()));

}

loginScreen::~loginScreen()
{
    delete ui;
}

void loginScreen::showError()
{
    ui->errorLabel->setVisible(true);
}

void loginScreen::on_connect_button_clicked()
{
   m_username = ui->usernameTextBox->text().toStdString();
   m_ip = ui->ipTextBox->text().toStdString();

    if (m_username.empty() || m_ip.empty())
        showError();
    else
    {

        boost::trim(m_username);
        std::cout << m_username << std::endl;

	    m_viewModel->setClientUsername(m_username);
	    m_viewModel->setIpServer(m_ip);

	    m_viewModel->connectToServer();



    }
}

void loginScreen::setM_viewModel(ViewModel *m_viewModel) {
	loginScreen::m_viewModel = m_viewModel;
}
