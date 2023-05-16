#pragma once

#include <QMainWindow>
#include <solutionwindow.h>
#include <problemtypewindow.h>

namespace Ui{
    class UploadWindow;
}

class UploadWindow : public QMainWindow{
    Q_OBJECT

private slots:
    void on_submit_button_clicked();
    void on_back_clicked();
    void on_upload_button_clicked();

public:
    explicit UploadWindow(QWidget* parent = nullptr);
    ~UploadWindow();

private:
    Ui::UploadWindow* ui;
    SolutionWindow* solutionWindow;
    ProblemTypeWindow* problemTypeWindow;
    std::string expression;

};

