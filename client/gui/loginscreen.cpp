#include <iostream>
#include "loginscreen.hpp"
#include "ui_loginscreen.h"
#include <boost/algorithm/string.hpp>


loginScreen::loginScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginScreen),
    m_client(nullptr)
{
    ui->setupUi(this);
    ui->usernameErrorLabel->setVisible(false);
}

loginScreen::~loginScreen()
{
    delete ui;
}

void loginScreen::on_connect_button_clicked()
{
   m_username = ui->usernameTextBox->text().toStdString();

    if (m_username.empty())
        ui->usernameErrorLabel->setVisible(true);
    else
    {

        boost::trim(m_username);
        std::cout << m_username << std::endl;

        m_client->test();

        hide();
        m_mainWindow = new MainWindow(this);
        m_mainWindow->show();
    }
}

void loginScreen::setM_client(Client *m_client) {
	loginScreen::m_client = m_client;
}
