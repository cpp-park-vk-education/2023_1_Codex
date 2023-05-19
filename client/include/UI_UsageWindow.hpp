/********************************************************************************
** Form generated from reading UI file 'usagewindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#pragma once

#include <QAction>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UsageWindow {
   public:
    QWidget* centralwidget;
    QLabel* label;
    QFrame* line;
    QTextBrowser* textBrowser;

    void setupUi(QMainWindow* MainWindow) {
        if (MainWindow->objectName().isEmpty()) MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setStyleSheet(QStringLiteral("background-color:rgb(31, 34, 41);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(320, 20, 171, 31));
        QFont font;
        font.setFamily(QStringLiteral("Arial Black"));
        font.setPointSize(16);
        font.setBold(true);
        font.setItalic(false);
        label->setFont(font);
        label->setStyleSheet(
            QLatin1String("color: rgb(255, 255, 255);\n"
                          "font: 900 16pt \"Arial Black\";"));
        line = new QFrame(centralwidget);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(290, 60, 220, 3));
        line->setStyleSheet(QStringLiteral("background-color: rgb(7, 197, 216);"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(15, 81, 771, 510));
        textBrowser->setStyleSheet(QStringLiteral("color:white; border:none;"));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    }  // setupUi

    void retranslateUi(QMainWindow* MainWindow) {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "How to use", Q_NULLPTR));
        textBrowser->setHtml(QApplication::translate(
            "MainWindow",
            "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" "
            "\"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
            "<html><head><meta name=\"qrichtext\" content=\"1\" /><meta charset=\"utf-8\" /><style "
            "type=\"text/css\">\n"
            "p, li { white-space: pre-wrap; }\n"
            "hr { height: 1px; border-width: 0; }\n"
            "li.unchecked::marker { content: \"\\2610\"; }\n"
            "li.checked::marker { content: \"\\2612\"; }\n"
            "</style></head><body style=\" font-family:'Segoe UI'; font-size:9pt; font-weight:400; "
            "font-style:normal;\">\n"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; "
            "-qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; color:#ffffff;\">This app "
            "can show you the prediction of stocks yield.</span></p>\n"
            "<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; "
            "-qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; color:#ffffff;\">All you "
            "need is:</span></p>\n"
            "<ul style=\"margin-top: 0px; margin-bottom: 0px; margin-left: 0px; margin-right: 0px; "
            "-qt-list-indent: 1;\">\n"
            "<li style=\" font-size:12pt; color:#ffffff;\" style=\" margin-top:12px; margin-bottom:0px; "
            "margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> Check the yield of "
            "your shares on the last 5 days and round up them</li>\n"
            "<li style=\" font-size:12pt; color:#ffffff;\" style=\" margin-top:12px; margin-bottom:0px; "
            "margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> Tap the "
            "&quot;Start&quot; button</li>\n"
            "<li style=\" font-size:12pt; color:#ffffff;\" style=\" margin-top:12px; margin-bottom:0px; "
            "margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> Enter the yield of "
            "your shares in the fields, one number in each field, the numbers must be integers</li>\n"
            "<li style=\" font-size:12pt; color:#ffffff;\" style=\" margin-top:12px; margin-bottom:0px; "
            "margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"> Finally, click the "
            "&quot;Submit&quot; button</li></ul>\n"
            "<p style=\" margin-top:12px; margin-bottom:0px"
            "; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" "
            "font-size:12pt; color:#ffffff;\">That's all! You will see your prediction in a few "
            "seconds!</span></p>\n"
            "<p style=\"-qt-paragraph-type:empty; margin-top:12px; margin-bottom:0px; margin-left:0px; "
            "margin-right:0px; -qt-block-indent:0; text-indent:0px; font-size:12pt; color:#ffffff;\"><br "
            "/></p>\n"
            "<p style=\" margin-top:12px; margin-bottom:0px; margin-left:0px; margin-right:0px; "
            "-qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt; color:#ffffff;\">To see "
            "the statistics for a particular indicator, click the appropriate button on the side "
            "bar</span></p></body></html>",
            Q_NULLPTR));
    }  // retranslateUi
};

namespace Ui {
class UsageWindow : public Ui_UsageWindow {};
}  // namespace Ui

QT_END_NAMESPACE
