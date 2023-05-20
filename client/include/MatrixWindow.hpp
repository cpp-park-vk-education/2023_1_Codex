#pragma once

#include <QMainWindow>

namespace Ui {
class MatrixWindow;
}

class MatrixWindow : public QMainWindow {
    Q_OBJECT

   public:
    explicit MatrixWindow(QWidget* parent = nullptr);
    ~MatrixWindow();

   private slots:
    void on_submit_button_clicked();

   private:
    Ui::MatrixWindow* ui;
    size_t width;
    size_t height;
};
