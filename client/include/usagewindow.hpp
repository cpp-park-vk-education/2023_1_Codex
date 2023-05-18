#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui{ class UsageWindow; }
QT_END_NAMESPACE

class UsageWindow : public QMainWindow{
    Q_OBJECT
public:
    UsageWindow(QWidget* parent = nullptr);
    ~UsageWindow();
private:
    Ui::UsageWindow* ui;
};
