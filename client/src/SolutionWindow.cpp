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
#include <QFileDialog>
#include <QPixmap>
#include <QImage>
#include <iostream>


#include "Client.hpp"
#include "ProblemTypeWindow.hpp"
#include "UI_SolutionWindow.hpp"
//#include "ProblemType.hpp"

using namespace std;

SolutionWindow::SolutionWindow(const Client::ClientSPtr& client, Client::TaskTypes taskTypeInp, QString value, QWidget* parent)
    : m_client(client), taskType(taskTypeInp), typeName(value), QMainWindow(parent), ui(new Ui::SolutionWindow) {
    ui->setupUi(this);
    setFixedSize(800, 600);
    mainLayout = std::make_shared<QVBoxLayout>(centralWidget());

    // Создание кнопки загрузки фото
    if (taskType == Client::Arithmetic){
        uploadImageButton = std::make_shared<QPushButton>("Upload\nimage", this);
        uploadImageButton->setGeometry(10, 100, 91, 91);
        uploadImageButton->setStyleSheet(
            "background-color: #15E099;color: white;font: 900 14pt \"Century Gothic\";\nborder-radius:10px;\n");
        connect(uploadImageButton.get(), &QPushButton::clicked, [=]() { getImagePath(); });
    }
    // Создание кнопки "Back"
    backButton = std::make_shared<QPushButton>("Back", this);
    backButton->setGeometry(10, this->height() - 60, 120,40);
    backButton->setStyleSheet(
        "background-color: #3F3D42; color: white;\nfont: 500 12pt \"Century Gothic\"; border-radius: 10");
    connect(backButton.get(), &QPushButton::clicked, this, &SolutionWindow::onBackButtonClicked);

    // Создание надписи "Title"
    QString title = "Solving: " + typeName;
    std::cout<<title.toStdString()<<std::endl;
    titleLabel = std::make_shared<QLabel>(title, this);
    titleLabel->setStyleSheet("color: white; padding: 10px; font: 500 20pt\"Century Gothic\"");
    titleLabel->setGeometry(0, 0, this->width(), 55);
    titleLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

    line = std::make_shared<QFrame>(centralWidget());
    line->setGeometry(0, 60, this->width(), 2);
    line->setStyleSheet("background-color:white");
    line->setFrameShape(QFrame::HLine);

    // Создание полей ответа
    textExpression = std::make_shared<QLabel>(this);
    textExpression->setGeometry(260, 100, this->width()-260-10,40);
    textExpression->setStyleSheet("color: white; font-size: 14px; font: \"Century Gothic\";border-style: solid; border-width: 1px; border-color: white;");// убрать бордер
    textExpression->setText("");

    textSolution = std::make_shared<QLabel>(this);
    textSolution->setGeometry(260, 150, this->width()-260-10,
        41);
    textSolution->setStyleSheet("color: white; font-size: 14px; font: \"Century Gothic\"; border-style: solid; border-width: 1px; border-color: white;");// убрать бордер
    textSolution->setText("");

    labelExpression = std::make_shared<QLabel>("Task:",this);
    labelExpression->setGeometry(150, 100, 100, 40);
    labelExpression->setStyleSheet("color: white; font-size: 18px; font: \"Century Gothic\"");
    labelSolution = std::make_shared<QLabel>("Solution:",this);
    labelSolution->setGeometry(150, 150, 100, 40);
    labelSolution->setStyleSheet("color: white; font-size: 18px; font: \"Century Gothic\"");


    // Создание полей ввода текста
    cout<<"taskType = " << taskType<< " "<< typeName.toStdString()<<endl;
    // для матриц
    if (taskType == Client::MatrixDet || taskType == Client::MatrixT || taskType == Client::MatrixEigen || taskType == Client::MatrixRank || taskType == Client::MatrixNorm){
        matrixInputForm = std::make_shared<MatrixInputForm>(this);
        mainLayout->addWidget(matrixInputForm.get(), 0, Qt::AlignBottom | Qt::AlignHCenter);
        mainLayout->setStretch(1, 1);

        QWidget* bottomSpacer = new QWidget();
        bottomSpacer->setFixedSize(1, 20);
        mainLayout->addWidget(bottomSpacer);
    }
    // интегралы
    else if (taskType == Client::IntegNewton || taskType == Client::IntegSimpson || taskType == Client::IntegTrapez) {
        integralLabel = std::make_shared<QLabel>("<html>&#x222B;</html>", this);
        integralLabel->setStyleSheet("color: white; font-size: 50px; font: \"Century Gothic\"");
        integralLabel->setGeometry(120, 320, 50, 100);

        lowerLimitField = std::make_shared<QLineEdit>(this);
        lowerLimitField->setStyleSheet("color: white; font-size: 14px; font: \"Century Gothic\";border-style: solid; border-width: 1px; border-color: white;");
        lowerLimitField->setGeometry(120-10, 320+110, 60, 30);
        upperLimitField = std::make_shared<QLineEdit>(this);
        upperLimitField->setStyleSheet("color: white; font-size: 14px; font: \"Century Gothic\";border-style: solid; border-width: 1px; border-color: white;");
        upperLimitField->setGeometry(120-10, 320-10, 60, 30);

        inputField = std::make_shared<QLineEdit>(this);
        inputField->setGeometry(120+70, 360, 350, 40);
        inputField->setStyleSheet("color: white; font-size: 16px; font: \"Century Gothic\"");

        dxLabel = std::make_shared<QLabel>("dx", this);
        dxLabel->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
        dxLabel->setGeometry(120+70+360, 320+40, 30, 30);

        numberOfNodesField = std::make_shared<QLineEdit>(this);
        numberOfNodesField->setGeometry(120+70+360+30, 360, 100, 40);
        numberOfNodesField->setStyleSheet("color: white; font-size: 16px; font: \"Century Gothic\"");

        nodesLabel = std::make_shared<QLabel>("nodes", this);
        nodesLabel->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
        nodesLabel->setGeometry(120+70+360+60, 320+80, 80, 30);
    }
    // комбинаторика
    else if (taskType == Client::CombComb || taskType == Client::CombRe || taskType == Client::CombPlace || taskType == Client::CombPart) {
        combLabel = std::make_shared<QLabel>("find C<sup>k</sup><sub>n</sub> with", this);
        combLabel->setStyleSheet("color: white; font-size: 24px; font: \"Century Gothic\"");
        combLabel->setGeometry(320, 320, 200, 40);

        nCombLabel = std::make_shared<QLabel>("n = ", this);
        nCombLabel->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
        nCombLabel->setGeometry(320-50, 320+80, 40, 30);

        nCombField = std::make_shared<QLineEdit>(this);
        nCombField->setStyleSheet("color: white; font-size: 14px; font: \"Century Gothic\";border-style: solid; border-width: 1px; border-color: white;");
        nCombField->setGeometry(320-50+40, 320+80, 60, 30);

        kCombLabel = std::make_shared<QLabel>("k = ", this);
        kCombLabel->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
        kCombLabel->setGeometry(320+100, 320+80, 40, 30);

        kCombField = std::make_shared<QLineEdit>(this);
        kCombField->setStyleSheet("color: white; font-size: 14px; font: \"Century Gothic\";border-style: solid; border-width: 1px; border-color: white;");
        kCombField->setGeometry(320+140, 320+80, 60, 30);
    }
    // дифференцирование
    else if (taskType == Client::DiffNum){
        dSignLeftBrace = std::make_shared<QLabel>("d(", this);
        dSignLeftBrace->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
        dSignLeftBrace->setGeometry(120, 400, 40, 30);

        diffField = std::make_shared<QLineEdit>(this);
        diffField->setStyleSheet("color: white; font-size: 14px; font: \"Century Gothic\";border-style: solid; border-width: 1px; border-color: white;");
        diffField->setGeometry(120+30, 400, 210, 30);

        rightBrace= std::make_shared<QLabel>(")", this);
        rightBrace->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
        rightBrace->setGeometry(120+30+220, 400, 40, 30);

        diffLine = std::make_shared<QFrame>(centralWidget());
        diffLine->setGeometry(100, 410+diffField->height(), 300, 1);
        diffLine->setStyleSheet("background-color:white");
        diffLine->setFrameShape(QFrame::HLine);

        dxLabel = std::make_shared<QLabel>("dx", this);
        dxLabel->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
        dxLabel->setGeometry(250, 410+diffField->height()+10, 30, 30);

        diffPointLabel = std::make_shared<QLabel>("at point x = ", this);
        diffPointLabel->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
        diffPointLabel->setGeometry(450, 410+diffField->height()-20, 100, 30);

        diffPointField = std::make_shared<QLineEdit>(this);
        diffPointField->setStyleSheet("color: white; font-size: 14px; font: \"Century Gothic\";border-style: solid; border-width: 1px; border-color: white;");
        diffPointField->setGeometry(570, 410+diffField->height()-20, 60, 40);
    }
    // линейные уравнения
    else if (taskType == Client::EqLin){
        aEquationsinputField = std::make_shared<QLineEdit>(this);
        aEquationsinputField->setGeometry(230, 360, 80, 30);
        aEquationsinputField->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");

        xEquationsLabel = std::make_shared<QLabel>("x + ", this);
        xEquationsLabel->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
        xEquationsLabel->setGeometry(330, 360, 80, 30);

        bEquationsinputField = std::make_shared<QLineEdit>(this);
        bEquationsinputField->setGeometry(380, 360, 80, 30);
        bEquationsinputField->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");

        constEquationsLabel = std::make_shared<QLabel>(" = 0", this);
        constEquationsLabel->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
        constEquationsLabel->setGeometry(480, 360, 80, 30);
    }
    // квадратные уравнения
    else if (taskType == Client::EqSq){
        aEquationsinputField = std::make_shared<QLineEdit>(this);
        aEquationsinputField->setGeometry(200, 360, 80, 30);
        aEquationsinputField->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");

        x2EquationsLabel = std::make_shared<QLabel>("x<sup>2</sup> + ", this);
        x2EquationsLabel->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
        x2EquationsLabel->setGeometry(300, 360, 80, 30);

        bEquationsinputField = std::make_shared<QLineEdit>(this);
        bEquationsinputField->setGeometry(350, 360, 80, 30);
        bEquationsinputField->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");

        xEquationsLabel = std::make_shared<QLabel>("x + ", this);
        xEquationsLabel->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
        xEquationsLabel->setGeometry(450, 360, 80, 30);

        cEquationsinputField = std::make_shared<QLineEdit>(this);
        cEquationsinputField->setGeometry(500, 360, 80, 30);
        cEquationsinputField->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");

        constEquationsLabel = std::make_shared<QLabel>(" = 0", this);
        constEquationsLabel->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
        constEquationsLabel->setGeometry(600, 360, 80, 30);
    }
    // СЛАУ
    else if(taskType == Client::EqSGauss || taskType == Client::EqSGaussM || taskType == Client::EqSLU){
        matrixInputForm = std::make_shared<MatrixInputForm>(this);
        matrixInputForm = std::make_shared<MatrixInputForm>(true, this);
        mainLayout->addWidget(matrixInputForm.get(), 0, Qt::AlignBottom | Qt::AlignHCenter);
        mainLayout->setStretch(1, 1);

        QWidget* bottomSpacer = new QWidget();
        bottomSpacer->setFixedSize(1, 20);
        mainLayout->addWidget(bottomSpacer);

    }
    // стандартное
    else{
        inputField = std::make_shared<QLineEdit>(this);
        inputField->setGeometry(120, 420, 551, 50);  //(10, this->height() - 80, this->width() - 120, 30);
        inputField->setStyleSheet("color: white; font-size: 16px; font: \"Century Gothic\"");
    }

    // Создание кнопки "OK"
    okButton = std::make_shared<QPushButton>("Solve", this);
    okButton->setGeometry(this->width() - 130, this->height() - 60, 120,40);
    okButton->setStyleSheet(
        "background-color: #15E099;\ncolor: rgb(255, 255, 255);\nfont: 900 12pt \"Century Gothic\"; border-radius: 10");
    connect(okButton.get(), &QPushButton::clicked, [=]() { getAnswer(); });
}

SolutionWindow::~SolutionWindow() {
    delete ui;
}

void SolutionWindow::onBackButtonClicked() {
    this->close();
    emit openProblemTypeWindow();
}

void SolutionWindow::setClient(const Client::ClientSPtr& client, const Client::TaskTypes taskTypeM) {
    m_client = client;
    taskType=taskTypeM;
}

void SolutionWindow::getImagePath() {
    QString fileName = QFileDialog::getOpenFileName(this, tr("Choose"), "", tr("Images (*.png *.jpg)"), nullptr, QFileDialog::Options(QFileDialog::DontUseNativeDialog | QFileDialog::ReadOnly));
        imgPath = fileName;
    cout<<imgPath.toStdString()<<endl;
    getAnswer(imgPath);
}

QString SolutionWindow::parseMatrix(){
    QString text = "";

    int rows = matrixInputForm->getRows();
    int cols = matrixInputForm->getCols();
    QVector<QVector<QLineEdit *>> matrixInputs = matrixInputForm->getMatrixInputs();

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            text += matrixInputs[row][col]->text() + " ";
        }
        if (row < rows-1){
            text += "/ ";
        }
    }
    return text;
}

QString SolutionWindow::parseIntegral(){
    QString text = "";
    text += inputField->text() + " , " + lowerLimitField->text() + " , " + upperLimitField->text() + " , " + numberOfNodesField->text();
    return text;
}

QString SolutionWindow::parseCombinatorics(){
    QString text = "";
    text += kCombField->text() + " " + nCombField->text();
    return text;
}

QString SolutionWindow::parseDifferentiation(){
    QString text = "";
    text += diffField->text() + " " + diffPointField->text();
    return text;
}

QString SolutionWindow::parseEqLin(){
    QString text = "";
    text += aEquationsinputField->text() + " " + bEquationsinputField->text();
    return text;
}

QString SolutionWindow::parseEqSq(){
    QString text = "";
    text += aEquationsinputField->text() + " " + bEquationsinputField->text() + " " + cEquationsinputField->text();
    return text;
}

QString SolutionWindow::parseLAES(){
    QString text = "";

    int rows = matrixInputForm->getRows();
    int cols = matrixInputForm->getCols();

    QVector<QVector<QLineEdit *>> matrixInputs = matrixInputForm->getMatrixInputs();

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            text += matrixInputs[row][col]->text() + " ";
        }
        if (row < rows-1){
            text += "/ ";
        }
    }
    text += ", ";
    QVector<QLineEdit *> equalsInputs = matrixInputForm->getEqualsInputs();
    for (QLineEdit * inp : equalsInputs) {
        text += inp->text() + " ";
    }
    return text;
}

void SolutionWindow::getAnswer() {
    QString text = "";
    cout<<"in get answer\n";
    if (taskType == Client::MatrixDet || taskType == Client::MatrixT || taskType == Client::MatrixEigen || taskType == Client::MatrixRank || taskType == Client::MatrixNorm){
        text = this->parseMatrix();
    }
    else if (taskType == Client::IntegNewton || taskType == Client::IntegSimpson || taskType == Client::IntegTrapez) {
        text = this->parseIntegral();
    }
    else if (taskType == Client::CombComb || taskType == Client::CombRe || taskType == Client::CombPlace || taskType == Client::CombPart) {
        text = this->parseCombinatorics();
    }
    else if (taskType == Client::DiffNum){
        text = this->parseDifferentiation();
    }
    else if (taskType == Client::EqLin){
        text = this->parseEqLin();
    }
    else if (taskType == Client::EqSq){
        text = this->parseEqSq();
    }
    else if(taskType == Client::EqSGauss || taskType == Client::EqSGaussM || taskType == Client::EqSLU){
        text = this->parseLAES();
    }
    else{
        text = inputField->text();//expression;
    }
    cout<<"TEXT: "<<text.toStdString()<<endl;

    //solutionResult = m_client.get()->Run(text.toStdString(), taskType);/////////////////////////////////
    solutionResult = Run(text.toStdString(), taskType);
    setExpressionSolution();
}

void SolutionWindow::getAnswer(QString expression) {
    QString text = expression;
    //solutionResult = m_client.get()->Run(text.toStdString(), taskType);/////////////////////////////////
    solutionResult = Run(text.toStdString(), taskType);
    setExpressionSolution();
}

void SolutionWindow::setExpressionSolution() {
    textExpression->setText(QString::fromStdString(solutionResult.TaskData));
    if (solutionResult.ErrorCode) {
        textSolution->setText(QString::fromStdString(solutionResult.TaskError));
    } else {
        textSolution->setText(QString::fromStdString(solutionResult.TaskAnswer));
    }
}

Client::TaskInfo SolutionWindow::Run(const std::string& expression, Client::TaskTypes taskType) {
    Client::TaskInfo taskInfo(expression, Client::TaskTypes::IntegNewton, "TASK ANSWER");
    return taskInfo;
}
void SolutionWindow::insertTypeName(QString value, Client::TaskTypes taskType) {
    this->typeName = value;
    this->taskType = taskType;
}

void SolutionWindow::onTypeNameSelected(QString typeName) {
    this->typeName = typeName;
}
