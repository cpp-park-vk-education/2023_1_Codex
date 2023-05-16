#pragma once

#include <QMainWindow>
#include <usagewindow.h>
#include <mainwindow.h>
#include <matrixwindow.h>

namespace Ui{
    class ProblemTypeWindow;
}

class ProblemTypeWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit ProblemTypeWindow(QWidget* parent = nullptr);
    ~ProblemTypeWindow();

private slots:
    void on_next_button_clicked();
    void on_back_clicked();

private:
    Ui::ProblemTypeWindow* ui;
    size_t problemType;
    UploadWindow* uploadWindow;
    MainWindow* mainWindow;
    MatrixWindow* matrixWindow;
};
