#include "loginscreen.h"
#include "ui_loginscreen.h"
#include <iostream>

LoginScreen::LoginScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginScreen)
{
    ui->setupUi(this);
}

LoginScreen::~LoginScreen()
{
    delete ui;
}

void LoginScreen::on_connectButton_clicked()
{
    std::cout << "Test" << std::endl;
    auto username = ui->usernameTextbox->text();

    std::cout << username.toStdString() << std::endl;
}
