#ifndef LOGINSCREEN_HPP
#define LOGINSCREEN_HPP

#include <iostream>
#include <QWidget>
#include "mainwindow.hpp"

namespace Ui {
class loginScreen;
}

class loginScreen : public QWidget
{
    Q_OBJECT

public:
    explicit loginScreen(QWidget *parent = 0);
    ~loginScreen();

private slots:
    void on_connect_button_clicked();

private:
    Ui::loginScreen *ui;
    MainWindow *m_mainWindow;
    std::string m_username;
};

#endif // LOGINSCREEN_HPP
