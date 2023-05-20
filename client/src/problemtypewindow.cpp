#include "ProblemTypeWindow.hpp"

#include <QComboBox>
#include <QMainWindow>
#include <QPushButton>
#include <QSharedPointer>
#include <QStyleFactory>
#include <QVBoxLayout>
#include <QWidget>

#include "ProblemType.hpp"

ProblemTypeWindow::ProblemTypeWindow(const Client::ClientSPtr& client, QWidget* parent)
    : m_client(client), QMainWindow(parent), ui(new Ui::ProblemTypeWindow){
    // ProblemTypeWindow::ProblemTypeWindow(QWidget* parent) : QMainWindow(parent), ui(new
    // Ui::ProblemTypeWindow){
    ui->setupUi(this);

    solutionWindow = std::make_shared<SolutionWindow>(client, typeName, this);
    //solutionWindow = std::make_shared<SolutionWindow>(typeName, this);
    connect(solutionWindow.get(), &SolutionWindow::openProblemTypeWindow, this, &ProblemTypeWindow::show);
    connect(this, &ProblemTypeWindow::clientAvailable, solutionWindow.get(), &SolutionWindow::setClient);

    typesChoosingLayout = new QVBoxLayout(centralWidget());

// Создаем выпадающий список
    int counter = 0;

    QMenu* menuArray[TaskTypesMap.size()]; // глобальные типы задач
    QVector<QAction*> actions[TaskTypesMap.size()]; // конкретные типы задач
    QPushButton* buttons[TaskTypesMap.size()]; // кнопки выпадающих меню

    QVector<Client::TaskTypes> taskTypes;

    for (QString type : TaskTypesGlobalNames){//TaskTypesMap.keys()){
        menuArray[counter] = new QMenu(type, nullptr);
        for (QString name : TaskTypesMap[type]){ // конкретные типы задач
            QAction* anotherAction = new QAction(name, nullptr);
            actions[counter] << anotherAction;
            //taskTypes.push_back(static_cast<Client::TaskTypes>(taskTypes.size())); // добавляем очередной элемент TaskTypes
            taskTypes.push_back(static_cast<Client::TaskTypes>(taskTypes.size() + 1));
            //connect(actions[counter].last(), &QAction::triggered, this, &ProblemTypeWindow::onTypeTriggered);
            connect(actions[counter].last(), &QAction::triggered, this, [=](){
                onTypeTriggered(name, static_cast<Client::TaskTypes>(taskTypes.size()));//taskTypes[counter]);
                });


            menuArray[counter]->addAction(actions[counter].last());
        }
        buttons[counter] = new QPushButton(type, this);
        buttons[counter]->setMenu(menuArray[counter]);
        buttons[counter]->setStyleSheet("background-color: rgb(58, 139, 91);;\ncolor: rgb(255, 255, 255);\nfont: 900 12pt \"Arial Black\";\nborder-radius:20px;\n");
        buttons[counter]->setGeometry(30, 20, 691, 61);

        typesChoosingLayout->addWidget(buttons[counter]);
        counter++;
    }

    centralWidget()->setLayout(typesChoosingLayout);

    backButton = new QPushButton("Back", this);
    backButton->setStyleSheet("color: white;\nborder: 2px solid white;\nfont: 900 10pt \"Arial Black\";\nborder-radius:9px;\n");
    connect(backButton, &QPushButton::clicked, this, &ProblemTypeWindow::onBackButtonClicked);
}

ProblemTypeWindow::~ProblemTypeWindow(){
    delete backButton;
    delete ui;
}

void ProblemTypeWindow::onTypeTriggered(QString value, Client::TaskTypes taskType){
    this->close();
    emit clientAvailable(m_client);
    solutionWindow->show();
    solutionWindow->insertTypeName(value, taskType);
}

void ProblemTypeWindow::onBackButtonClicked(){
    this->close();
    emit openMainWindow();
}

void ProblemTypeWindow::setClient(const Client::ClientSPtr& client){
    m_client = client;
}
