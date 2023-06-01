/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow {
   public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QPushButton *usageButton;
    QPushButton *startButton;
    QLabel *label;
    QFrame *line;
    QFrame *line_2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow) {
        if (MainWindow->objectName().isEmpty()) MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(812, 600);
        MainWindow->setStyleSheet(QStringLiteral("background-color:rgb(31, 34, 41);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        centralwidget->setStyleSheet(QStringLiteral("background-color:rgb(42, 37, 47)"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(90, 280, 631, 171));
        groupBox->setStyleSheet(
            QLatin1String("border-width:2px;\n"
                          "border-color:white;\n"
                          "border-radius:10px;"));
        usageButton = new QPushButton(groupBox);
        usageButton->setObjectName(QStringLiteral("usageButton"));
        usageButton->setGeometry(QRect(40, 90, 200, 60));
        usageButton->setStyleSheet(
            QLatin1String("background-color: #17956A;\n"
                          "color: rgb(255, 255, 255);\n"
                          "font: 14pt \"Century Gothic\";\n"
                          "border-radius:20px;\n"
                          ""));
        startButton = new QPushButton(groupBox);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(400, 90, 200, 60));
        startButton->setStyleSheet(
            QLatin1String("background-color: #17956A;\n"
                          "color: rgb(255, 255, 255);\n"
                          "font: 14pt \"Century Gothic\";\n"
                          "border-radius:20px;\n"
                          ""));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(200, 10, 261, 41));
        QFont font;
        font.setFamily(QStringLiteral("Century Gothic"));
        font.setPointSize(20);
        font.setBold(false);
        font.setItalic(false);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral(
            "color:white;font-family:'Century Gothic'; font-size:20pt; font-weight:500; font-style:normal;"));
        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(90, 270, 630, 3));
        line->setStyleSheet(QStringLiteral("background-color:rgb(106, 108, 114);"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(90, 460, 630, 3));
        line_2->setStyleSheet(QStringLiteral("background-color:rgb(106, 108, 114);"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(610, 480, 191, 51));
        label_2->setStyleSheet(
            QLatin1String("color: rgb(201, 173, 214);\n"
                          "\n"
                          "font: 10pt \"Century Gothic\";"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(250, 60, 291, 61));
        QFont font1;
        font1.setFamily(QStringLiteral("Century Gothic"));
        font1.setPointSize(32);
        font1.setBold(true);
        font1.setItalic(false);
        label_3->setFont(font1);
        label_3->setStyleSheet(QStringLiteral(
            "color:white;font-family:'Century Gothic'; font-size:32pt; font-weight:700; font-style:normal;"));
        label_3->setTextFormat(Qt::AutoText);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(230, 150, 311, 31));
        QFont font2;
        font2.setFamily(QStringLiteral("Century Gothic"));
        font2.setPointSize(12);
        font2.setBold(false);
        font2.setItalic(false);
        label_4->setFont(font2);
        label_4->setStyleSheet(
            QLatin1String("color:rgb(201, 173, 214);\n"
                          "\n"
                          "font: 12pt \"Century Gothic\";\n"
                          "align-text: center;\n"
                          ""));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 812, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    }  // setupUi

    void retranslateUi(QMainWindow *MainWindow) {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        groupBox->setTitle(QString());
        usageButton->setText(QApplication::translate("MainWindow", "How to use", Q_NULLPTR));
        startButton->setText(QApplication::translate("MainWindow", "Start!", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Let's get started!", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "By: Codex team", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "MathVision", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Smart mathematical calculator", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    }  // retranslateUi
};

namespace Ui {
class MainWindow : public Ui_MainWindow {};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_MAINWINDOW_H
