#pragma once

#include <QMainWindow>
#include <usagewindow.h>
#include <problemtypewindow.h>

namespace Ui{
    class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    UsageWindow* usageWindow;
    ProblemTypeWindow* problemTypeWindow;
};

