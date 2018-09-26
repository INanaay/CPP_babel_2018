#include <iostream>
#include "loginscreen.hpp"
#include "ui_loginscreen.h"

loginScreen::loginScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginScreen)
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
        std::cout << m_username << std::endl;

        hide();
        m_mainWindow = new MainWindow(this);
        m_mainWindow->show();
    }
}
