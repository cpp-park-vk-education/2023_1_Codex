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

#include "Client.hpp"
#include "MatrixInputForm.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class SolutionWindow;
}
QT_END_NAMESPACE

class SolutionWindow : public QMainWindow {
    Q_OBJECT
   public:
    SolutionWindow(const Client::ClientSPtr& client, Client::TaskTypes taskTypeInp, QString value = "",
                   QWidget* parent = NULL);
    ~SolutionWindow();

    void insertTypeName(QString value, Client::TaskTypes taskType);
    Client::TaskInfo Run(const std::string& expression, Client::TaskTypes taskType);
    void setExpressionSolution();
    void updateTaskType(Client::TaskTypes taskType);

   private:
    QString typeName;
    Client::TaskTypes taskType;
    Ui::SolutionWindow* ui;
    Client::ClientSPtr m_client;
    Client::TaskInfo solutionResult;
    QString imgPath;

    std::shared_ptr<QPushButton> backButton;
    std::shared_ptr<QLabel> imageLabel;
    std::shared_ptr<QLabel> titleLabel;
    std::shared_ptr<QLabel> textExpression;
    std::shared_ptr<QLabel> textSolution;
    std::shared_ptr<QLineEdit> inputField;
    std::shared_ptr<QPushButton> okButton;
    std::shared_ptr<QPushButton> uploadImageButton;
    std::shared_ptr<MatrixInputForm> matrixInputForm;
    std::shared_ptr<QLabel> labelExpression;
    std::shared_ptr<QLabel> labelSolution;
    std::shared_ptr<QFrame> line;
    std::shared_ptr<QLabel> integralLabel;
    std::shared_ptr<QLineEdit> upperLimitField;
    std::shared_ptr<QLineEdit> lowerLimitField;
    std::shared_ptr<QLabel> dxLabel;
    std::shared_ptr<QLabel> nodesLabel;
    std::shared_ptr<QLineEdit> numberOfNodesField;
    std::shared_ptr<QLabel> combLabel;
    std::shared_ptr<QLabel> nCombLabel;
    std::shared_ptr<QLabel> kCombLabel;
    std::shared_ptr<QLineEdit> kCombField;
    std::shared_ptr<QLineEdit> nCombField;
    std::shared_ptr<QLabel> dSignLeftBrace;
    std::shared_ptr<QLabel> rightBrace;
    std::shared_ptr<QLineEdit> diffField;
    std::shared_ptr<QFrame> diffLine;
    std::shared_ptr<QLabel> diffPointLabel;
    std::shared_ptr<QLineEdit> diffPointField;
    std::shared_ptr<QLineEdit> aEquationsinputField;
    std::shared_ptr<QLineEdit> bEquationsinputField;
    std::shared_ptr<QLineEdit> cEquationsinputField;
    std::shared_ptr<QLabel> xEquationsLabel;
    std::shared_ptr<QLabel> constEquationsLabel;
    std::shared_ptr<QLabel> x2EquationsLabel;
    std::shared_ptr<QLabel> polinomialLabel;
    std::shared_ptr<QLabel> iterationsEquationsLabel;
    std::shared_ptr<QLineEdit> iterationsEquationsinputField;

    std::shared_ptr<QVBoxLayout> mainLayout;

    QString parseMatrix();
    QString parseIntegral();
    QString parseCombinatorics();
    QString parseDifferentiation();
    QString parseEqLin();
    QString parseEqSq();
    QString parseLAES();
    QString parsePoly();

   signals:
    void openProblemTypeWindow();

   private slots:
    void onBackButtonClicked();
    void onTypeNameSelected(QString typeName);
    void getAnswer(QString expression);
    void getAnswer();
    void getImagePath();

   public slots:
    void setClient(const Client::ClientSPtr& client, const Client::TaskTypes taskType_m);
};
