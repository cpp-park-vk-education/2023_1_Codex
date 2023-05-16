
#ifndef PROBLEMTYPEWINDOW_H
#define PROBLEMTYPEWINDOW_H
#include <QWidget>
#include <QApplication>
#include <QMainWindow>
#include "ui_problemtypewindow.h"
#include "solutionwindow.h"
//#include "problemType.h"

#include "taskInfo.hpp"
#include "client.hpp"

QT_BEGIN_NAMESPACE
namespace Ui{ class ProblemTypeWindow; }
QT_END_NAMESPACE

class ProblemTypeWindow : public QMainWindow{
    Q_OBJECT
public:
    //ProblemTypeWindow(Client::Client& client, QWidget *parent = nullptr);
    ProblemTypeWindow(QWidget* parent = nullptr);
    ~ProblemTypeWindow();

signals:
    void openMainWindow();
    void typeNameSelected(QString typeName);
    void clientAvailable(Client::Client& client);


private slots:
    void onTypeTriggered(QString value, Client::TaskTypes taskType);
    void onBackButtonClicked();

private:
         //QString TaskTypesHandlersNames[taskTypesNum];
    Ui::ProblemTypeWindow* ui;
    std::shared_ptr<SolutionWindow> solutionWindow;
    QString typeName;
    Client::TaskTypes taskType;
    QVBoxLayout* typesChoosingLayout;
    QPushButton* backButton;
    /*QMenu* menuArray[TaskTypesMap.size()]; // глобальные типы задач
    QVector<QAction *> actions[TaskTypesMap.size()]; // конкретные типы задач
    QPushButton *buttons[TaskTypesMap.size()]; // кнопки выпадающих меню
    */
    /*QVector<QMenu*> menuArray;
    QVector<QVector<QAction*>> actions;
    QVector<QPushButton*> buttons;*/

    //Client::Client& m_client;



public slots:
    void setClient(Client::Client& client);
};

#endif // PROBLEMTYPEWINDOW_H
