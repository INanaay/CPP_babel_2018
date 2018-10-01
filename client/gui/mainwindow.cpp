#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QRect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
	std::cout << "sup" << std::endl;
    ui->setupUi(this);

    QRect desktopRect = QApplication::desktop()->availableGeometry(this);
    QPoint center = desktopRect.center();
    move(center.x() - width() * 0.5, center.y() - height() * 0.5);
    m_model = new QStringListModel(this);


    ui->contactsListView->setEditTriggers(0);
    //populateContactList(list);
    std::cout << "Initialized main window" << std::endl;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::populateContactList(const std::vector<Contact> &list)
{
    std::cout << "Populating list in main window" << std::endl;
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

	std::cout << index.row() << std::endl;
}

void MainWindow::setM_viewModel(const ViewModel *m_viewModel) {
	MainWindow::m_viewModel = m_viewModel;
}
