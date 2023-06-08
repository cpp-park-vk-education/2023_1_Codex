#include "UsageWindow.hpp"

#include "UI_UsageWindow.hpp"

UsageWindow::UsageWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::UsageWindow) {
    ui->setupUi(this);
    setFixedSize(800, 600);
}

UsageWindow::~UsageWindow() {
    delete ui;
}
