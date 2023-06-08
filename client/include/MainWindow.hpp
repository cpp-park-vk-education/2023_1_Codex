#pragma once

#include <QMainWindow>
#include <memory>

#include "Client.hpp"
#include "ProblemTypeWindow.hpp"
#include "UI_MainWindow.hpp"
#include "UsageWindow.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

   public:
    MainWindow(const Client::ClientSPtr& client, QWidget* parent = NULL);
    ~MainWindow();
    void setClient(const Client::ClientSPtr& client);
   private slots:
    // Слоты от кнопок главного окна
    void on_usageButton_clicked();
    void on_startButton_clicked();

   signals:
    void clientAvailable(const Client::ClientSPtr& client);

   private:
    Ui::MainWindow* ui;
    std::shared_ptr<ProblemTypeWindow> problemTypeWindow;
    std::shared_ptr<UsageWindow> usageWindow;
    Client::ClientSPtr m_client;
};
