/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QAction>
#include <QtCore/QVariant>
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

    void setupUi(QMainWindow *MainWindow) {
        if (MainWindow->objectName().isEmpty()) MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(812, 600);
        MainWindow->setStyleSheet(QStringLiteral("background-color:rgb(31, 34, 41);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
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
            QLatin1String("background-color: rgb(70, 224, 130);\n"
                          "color: rgb(255, 255, 255);\n"
                          "font: 900 12pt \"Arial Black\";\n"
                          "border-radius:9px;\n"
                          ""));
        startButton = new QPushButton(groupBox);
        startButton->setObjectName(QStringLiteral("startButton"));
        startButton->setGeometry(QRect(400, 90, 200, 60));
        startButton->setStyleSheet(
            QLatin1String("background-color: rgb(70, 224, 130);\n"
                          "color: rgb(255, 255, 255);\n"
                          "font: 900 12pt \"Arial Black\";\n"
                          "border-radius:9px;\n"
                          ""));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(160, 10, 321, 41));
        QFont font;
        font.setFamily(QStringLiteral("Arial Black"));
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(false);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral(
            "color:white;font-family:'Arial Black'; font-size:20pt; font-weight:700; font-style:normal;"));
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
            QLatin1String("color:rgb(106, 108, 114);\n"
                          "font: 12pt \"Arial Narrow\";"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(240, 60, 331, 61));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial Black"));
        font1.setPointSize(32);
        font1.setBold(true);
        font1.setItalic(false);
        label_3->setFont(font1);
        label_3->setStyleSheet(QStringLiteral(
            "color:white;font-family:'Arial Black'; font-size:32pt; font-weight:700; font-style:normal;"));
        label_3->setTextFormat(Qt::AutoText);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(220, 150, 381, 31));
        QFont font2;
        font2.setFamily(QStringLiteral("Arial Narrow"));
        font2.setPointSize(16);
        font2.setBold(false);
        font2.setItalic(false);
        label_4->setFont(font2);
        label_4->setStyleSheet(
            QLatin1String("color:rgb(106, 108, 114);\n"
                          "\n"
                          "font: 16pt \"Arial Narrow\";"));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 812, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

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
        label_4->setText(QApplication::translate(
            "MainWindow",
            "\320\243\320\274\320\275\321\213\320\271 "
            "\320\274\320\260\321\202\320\265\320\274\320\260\321\202\320\270\321\207\320\265\321\201\320\272"
            "\320\270\320\271 "
            "\320\272\320\260\320\273\321\214\320\272\321\203\320\273\321\217\321\202\320\276\321\200",
            Q_NULLPTR));
    }  // retranslateUi
};

namespace Ui {
class MainWindow : public Ui_MainWindow {};
}  // namespace Ui

QT_END_NAMESPACE

#endif  // UI_MAINWINDOW_H
