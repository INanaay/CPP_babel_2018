#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QStringListModel>
#include <QMainWindow>
#include <client/inc/client/client.hpp>
#include <client/inc/viewmodel/ViewModel.hpp>

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
    void populateContactList(const std::vector<std::string> &list);
    void setM_viewModel(const ViewModel *m_viewModel);


private:
    Ui::MainWindow *ui;
    QStringListModel *m_model;
    QStringList m_stringList;
    const ViewModel *m_viewModel;

private slots:
    void on_callButton_clicked();
};

#endif // MAINWINDOW_HPP
