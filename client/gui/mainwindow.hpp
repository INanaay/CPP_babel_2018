#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QStringListModel>
#include <QMainWindow>
#include <client/inc/client/client.hpp>
#include <client/inc/viewmodel/ViewModel.hpp>
#include "client/inc/common/contacts.hpp"

class ViewModel;

class Client;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void populateContactList(const std::vector<Contact> &list);
    void setM_viewModel(const ViewModel *m_viewModel);
    void showCallPopup(const std::string &username);
    void hideCallPopup();

private:
	Ui::MainWindow *ui;
	QStringListModel *m_model;
	QStringList m_stringList;
	const ViewModel *m_viewModel;

private slots:
    void on_callButton_clicked();
    void on_acceptButton_clicked();
};

#endif // MAINWINDOW_HPP
