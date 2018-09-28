#ifndef LOGINSCREEN_HPP
#define LOGINSCREEN_HPP

#include <iostream>
#include <QWidget>
#include <client/inc/viewmodel/ViewModel.hpp>
#include "mainwindow.hpp"
#include "client/inc/client/client.hpp"


class ViewModel;

namespace Ui {
class loginScreen;
}

class loginScreen : public QWidget
{
    Q_OBJECT

public:
    explicit loginScreen(QWidget *parent = 0);
    ~loginScreen();
    void setM_viewModel(ViewModel *m_viewModel);


private slots:
    void on_connect_button_clicked();

private:
    Ui::loginScreen *ui;
    std::string m_username;
    ViewModel *m_viewModel;
};

#endif // LOGINSCREEN_HPP
