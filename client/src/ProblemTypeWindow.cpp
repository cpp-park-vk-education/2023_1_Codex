#include "ProblemTypeWindow.hpp"

#include <QComboBox>
#include <QMainWindow>
#include <QPushButton>
#include <QRect>
#include <QSharedPointer>
#include <QStyleFactory>
#include <QVBoxLayout>
#include <QWidget>
#include <iostream>

#include "ProblemType.hpp"
#include "SolutionWindow.hpp"

ProblemTypeWindow::ProblemTypeWindow(const Client::ClientSPtr& client, QWidget* parent)
    : m_client(client), QMainWindow(parent), ui(new Ui::ProblemTypeWindow) {
    ui->setupUi(this);
    setFixedSize(800, 600);

    // chooseTypeLabel
    chooseTypeLabel = std::make_shared<QLabel>("Choose a task type", this);
    chooseTypeLabel->setStyleSheet("color: white; padding: 10px; font: 500 20pt\"Century Gothic\"");
    chooseTypeLabel->setGeometry(0, 0, this->width(), 50);
    chooseTypeLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    // Создаем выпадающий список
    int counter = 0;

    QMenu* menuArray[TaskTypesMap.size()];           // глобальные типы задач
    QVector<QAction*> actions[TaskTypesMap.size()];  // конкретные типы задач
    QPushButton* buttons[TaskTypesMap.size()];       // кнопки выпадающих меню

    QString menuStyle =
        "QMenu {"
        "    background-color: #F0F0F0;"
        "}"
        "QMenu::item {"
        "    padding: 8px 20px;  /* размеры элементов меню */"
        "    background-color: #15E099;"
        "    text-align: center;"
        "    color: white;"
        "    font: 500 14pt \"Century Gothic\";"
        "}"
        "QMenu::item:selected {"
        "    background-color: #3F3D42;"
        "    color: white;"
        "}";

    QVector<Client::TaskTypes> taskTypes;
    size_t buttonWidth = this->width(), buttonHeight = 50, buttonSpace = 2, buttonTopMargin = 60;
    for (QString type : TaskTypesGlobalNames) {  // TaskTypesMap.keys()){
        buttons[counter] = new QPushButton(type, this);
        buttons[counter]->setStyleSheet(
            "background-color: #17956A;\ncolor: rgb(255, 255, 255);\nfont: 500 16pt \"Century Gothic\";");
        buttons[counter]->setGeometry(buttonSpace, buttonTopMargin + counter * (buttonHeight + buttonSpace),
                                      buttonWidth - buttonSpace, buttonHeight);

        menuArray[counter] = new QMenu(type, nullptr);
        menuArray[counter]->setStyleSheet(menuStyle);
        menuArray[counter]->setFixedWidth(buttons[counter]->width());
        // menuArray[counter]->exec(buttons[counter]->mapToGlobal(QPoint(0, buttons[counter]->height()))); //
        // Отображение выпадающего меню по центру виджета
        for (QString name : TaskTypesMap[type]) {  // конкретные типы задач
            QAction* anotherAction = new QAction(name, nullptr);
            actions[counter] << anotherAction;
            // taskTypes.push_back(static_cast<Client::TaskTypes>(taskTypes.size())); // добавляем очередной
            // элемент TaskTypes
            taskTypes.push_back(static_cast<Client::TaskTypes>(taskTypes.size() + 1));
            // connect(actions[counter].last(), &QAction::triggered, this,
            // &ProblemTypeWindow::onTypeTriggered);
            connect(actions[counter].last(), &QAction::triggered, this,
                    [=]() { onTypeTriggered(name, static_cast<Client::TaskTypes>(taskTypes.size())); });

            menuArray[counter]->addAction(actions[counter].last());
        }

        buttons[counter]->setMenu(menuArray[counter]);

        // typesChoosingLayout->addWidget(buttons[counter]);
        counter++;
    }

    backButton = new QPushButton("Back", this);
    backButton->setStyleSheet(
        "background-color: #3F3D42; color: white;\nfont: 500 12pt \"Century Gothic\"; border-radius: 10");
    backButton->setGeometry(20, 10, 120, 40);
    connect(backButton, &QPushButton::clicked, this, &ProblemTypeWindow::onBackButtonClicked);
}

ProblemTypeWindow::~ProblemTypeWindow() {
    delete backButton;
    delete ui;
}

void ProblemTypeWindow::onTypeTriggered(QString value, Client::TaskTypes taskType) {
    solutionWindow = std::make_shared<SolutionWindow>(m_client, taskType, value, this);
    connect(solutionWindow.get(), &SolutionWindow::openProblemTypeWindow, this, &ProblemTypeWindow::show);
    this->close();
    std::cout << "taskType origin " << taskType << std::endl;
    std::cout << "taskName origin " << value.toStdString() << std::endl;
    solutionWindow->insertTypeName(value, taskType);
    solutionWindow->show();
}

void ProblemTypeWindow::onBackButtonClicked() {
    this->close();
    emit openMainWindow();
}

void ProblemTypeWindow::setClient(const Client::ClientSPtr& client) {
    m_client = client;
}
