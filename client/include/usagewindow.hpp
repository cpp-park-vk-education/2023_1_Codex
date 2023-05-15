#pragma once

#include <QMainWindow>

namespace Ui{
    class UsageWindow;
}

class UsageWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit UsageWindow(QWidget* parent = nullptr);
    ~UsageWindow();

private:
    Ui::UsageWindow* ui;
};

