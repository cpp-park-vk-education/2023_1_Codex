#include "SolutionWindow.hpp"

#include <string.h>

#include <QComboBox>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QStyleFactory>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

#include "Client.hpp"
#include "ProblemTypeWindow.hpp"
#include "UI_SolutionWindow.hpp"
using namespace std;

SolutionWindow::SolutionWindow(const Client::ClientSPtr& client, QString value, QWidget* parent)
    : m_client(client), typeName(value), QMainWindow(parent), ui(new Ui::SolutionWindow){
    // SolutionWindow::SolutionWindow(QString value, QWidget* parent) : typeName(value), QMainWindow(parent),
    // ui(new Ui::SolutionWindow){
    ui->setupUi(this);
    //getAnswer("");
    //connect(solutionWindow, &ProblemTypeWindow::typeNameSelected, this, &SolutionWindow::onTypeNameSelected);

    // Создание кнопки "Back"
    backButton = std::make_shared<QPushButton>("Back", this);
    backButton->setGeometry(10, this->height() - 40, 80, 30);
    backButton->setStyleSheet(
        "color: white;\nborder: 2px solid white;\nfont: 900 10pt \"Arial Black\";\nborder-radius:9px;\n");
    connect(backButton.get(), &QPushButton::clicked, this, &SolutionWindow::onBackButtonClicked);

    // Создание надписи "Title"
    QString title = "Solving: " + typeName;

    titleLabel = std::make_shared<QLabel>(title, this);
    titleLabel->setStyleSheet("color: black; font-size: 24px; padding: 10px; font: \"Arial Black\"");
    titleLabel->setGeometry(0, 0, this->width(), 50);
    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    // Создание текстовых полей
    textExpression = std::make_shared<QLabel>(this);
    textExpression->setGeometry(110, 10, 651, 41);//(10, 60, this->width() - 20, (this->height() - 150) / 2);
    textExpression->setStyleSheet("color: white; font-size: 14px; font: \"Arial Black\"");
    textExpression->setText("");

    textSolution = std::make_shared<QLabel>(this);
    textSolution->setGeometry(120, 60, 651, 41);//(10, 70 + (this->height() - 150) / 2, this->width() - 20, (this->height() - 150) / 2);
    textSolution->setStyleSheet("color: white; font-size: 14px; font: \"Arial Black\"");
    textSolution->setText("");

    // Создание поля ввода текста
    inputField = std::make_shared<QLineEdit>(this);
    inputField->setGeometry(120, 460, 551, 81);  //(10, this->height() - 80, this->width() - 120, 30);
    inputField->setStyleSheet("color: white; font-size: 14px; font: \"Arial Black\"");

    // Создание кнопки "OK"
    okButton = std::make_shared<QPushButton>("OK", this);
    okButton->setGeometry(this->width() - 90, this->height() - 40, 80, 30);
    okButton->setStyleSheet(
        "background-color: rgb(70, 224, 130);\ncolor: rgb(255, 255, 255);\nfont: 900 12pt \"Arial "
        "Black\";\nborder-radius:9px;\n");
    // std::cout << title.toStdString() << std::endl;
    // std::cout << typeName.toStdString() << std::endl;
    connect(okButton.get(), &QPushButton::clicked, [=](){ getAnswer(inputField->text()); });
}

SolutionWindow::~SolutionWindow(){
    delete ui;
}

void SolutionWindow::onBackButtonClicked(){
    this->close();
    emit openProblemTypeWindow();
}

void SolutionWindow::setClient(const Client::ClientSPtr& client){
    m_client = client;
}

void SolutionWindow::getAnswer(QString expression){
    QString text = expression;
    // cout<<m_client.Run(text.toStdString(), taskType).TaskData<<endl;
    solutionResult = m_client.get()->Run(expression.toStdString(), taskType);
    // solutionResult = this->Run(expression.toStdString(), taskType);
    setExpressionSolution();
    // taskType = solutionResult.TaskType;
}

void SolutionWindow::setExpressionSolution(){
    textExpression->setText(QString::fromStdString(solutionResult.TaskData));
    if (solutionResult.ErrorCode){
        textSolution->setText(QString::fromStdString(solutionResult.TaskError));
    }
    else{
        textSolution->setText(QString::fromStdString(solutionResult.TaskAnswer));
    }
}

Client::TaskInfo SolutionWindow::Run(const std::string& expression, Client::TaskTypes taskType){
    Client::TaskInfo taskInfo("TASK DATA", Client::TaskTypes::IntegNewton, "TASK ANSWER");
    return taskInfo;
}
void SolutionWindow::insertTypeName(QString value, Client::TaskTypes taskType){
    this->typeName = value;
    this->taskType = taskType;
}

void SolutionWindow::onTypeNameSelected(QString typeName){
    this->typeName = typeName;
}
