#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QRect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Babel");

    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x() - width() * 0.5, center.y() - height() * 0.5);
    m_model = new QStringListModel(this);

    ui->callPopup->hide();

    ui->contactsListView->setEditTriggers(0);
    //populateContactList(list);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateContactList(const std::vector<Contact> &list)
{
    m_stringList.clear();

    for (const auto &contact : list)
    {
    	std::cout << contact.username << std::endl;
    	m_stringList.append( QString::fromStdString(contact.username));
    }


    m_model->setStringList(m_stringList);

    ui->contactsListView->setModel(m_model);
}

void MainWindow::on_callButton_clicked()
{

	auto index = ui->contactsListView->currentIndex();

	//std::cout << index.row() << std::endl;
	m_viewModel->startCall(index.row());
}

void MainWindow::setM_viewModel(const ViewModel *m_viewModel) {
	MainWindow::m_viewModel = m_viewModel;
}

void MainWindow::showCallPopup(const std::string &username)
{
    QString user = QString::fromStdString(username);
    ui->usernamePopupLabel->setText(user);
    ui->callPopup->show();
}

void MainWindow::hideCallPopup()
{
    ui->callPopup->hide();
}

void MainWindow::on_acceptButton_clicked()
{
	m_viewModel->acceptCall();
}
