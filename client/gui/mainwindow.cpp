#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_client(nullptr)
{
    ui->setupUi(this);
    m_model = new QStringListModel(this);

    std::vector<std::string> list;
    populateContactList(list);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateContactList(const std::vector<std::string> &list)
{
    std::cout << "Populating list" << std::endl;
    m_stringList.clear();

    for (int index = 0; index < 3; index++)
    {
        QString lol = QString::fromStdString("lol");
        m_stringList.append(lol);
    }

    m_model->setStringList(m_stringList);

    ui->contactsListView->setModel(m_model);
}

void MainWindow::setM_client(Client *m_client) {
	MainWindow::m_client = m_client;
}

void MainWindow::on_callButton_clicked()
{
    std::cout << "Yo" << std::endl;

    auto index = ui->contactsListView->currentIndex();

   std::cout << index.row() << std::endl;
}
