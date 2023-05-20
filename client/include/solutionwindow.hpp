#pragma once

#include <QApplication>
#include <QComboBox>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QStyleFactory>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <QWidget>

#include "client.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class SolutionWindow;
}
QT_END_NAMESPACE

class SolutionWindow : public QMainWindow {
    Q_OBJECT
   public:
    SolutionWindow(const Client::ClientSPtr& client, QString value = "", QWidget* parent = NULL);
    // SolutionWindow(QString value = "", QWidget* parent = nullptr);
    ~SolutionWindow();

    void insertTypeName(QString value, Client::TaskTypes taskType);
    Client::TaskInfo Run(const std::string& expression, Client::TaskTypes taskType);
    void setExpressionSolution();

   private:
    QString typeName;
    Client::TaskTypes taskType;
    Ui::SolutionWindow* ui;
    Client::ClientSPtr m_client;
    Client::TaskInfo solutionResult;

    std::shared_ptr<QPushButton> backButton;
    std::shared_ptr<QLabel> titleLabel;
    std::shared_ptr<QLabel> textExpression;
    std::shared_ptr<QLabel> textSolution;
    std::shared_ptr<QLineEdit> inputField;
    std::shared_ptr<QPushButton> okButton;

   signals:
    void openProblemTypeWindow();
   private slots:
    void onBackButtonClicked();
    void onTypeNameSelected(QString typeName);
    void getAnswer(QString expression);

   public slots:
    void setClient(const Client::ClientSPtr& client);
};
