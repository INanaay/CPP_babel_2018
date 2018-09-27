#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QStringListModel>
#include <QMainWindow>
#include <client/inc/client/client.hpp>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void populateContactList(const std::vector<std::string> &list);

private:
    Ui::MainWindow *ui;
    Client *m_client;
    QStringListModel *m_model;
    QStringList m_stringList;

public:
	void setM_client(Client *m_client);
private slots:
    void on_callButton_clicked();
};

#endif // MAINWINDOW_HPP
