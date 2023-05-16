
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>


#include "problemtypewindow.h"
#include "usagewindow.h"
#include "ui_mainwindow.h"
#include "client.hpp"

QT_BEGIN_NAMESPACE
namespace Ui{ class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    //MainWindow(Client::Client& client, QWidget* parent = NULL);
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void setClient(Client::Client& client);
private slots:
    // Слоты от кнопок главного окна
    void on_usageButton_clicked();
    void on_startButton_clicked();

signals:
    void clientAvailable(Client::Client& client);

private:
    Ui::MainWindow* ui;
    std::shared_ptr<ProblemTypeWindow> problemTypeWindow;
    std::shared_ptr<UsageWindow> usageWindow;
    //Client::Client& m_client;
};

#endif // MAINWINDOW_H
