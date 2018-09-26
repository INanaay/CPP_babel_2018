#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_client(nullptr)
{
    ui->setupUi(this);

    m_client->test();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setM_client(Client *m_client) {
	MainWindow::m_client = m_client;
}
