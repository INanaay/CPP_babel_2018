#include "loginscreen.h"
#include "ui_loginscreen.h"
#include <iostream>

LoginScreen::LoginScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginScreen)
{
    ui->setupUi(this);
    ui->errorLabel->setVisible(false);
}

LoginScreen::~LoginScreen()
{
    delete ui;
}

void LoginScreen::on_connectButton_clicked()
{
    std::cout << "Test" << std::endl;
    auto username = ui->usernameTextbox->text().toStdString();

    if (username.empty())
        ui->errorLabel->setVisible(true);

    std::cout << username << std::endl;
}
