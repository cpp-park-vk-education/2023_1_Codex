#include "UsageWindow.hpp"

#include "UI_UsageWindow.hpp"

UsageWindow::UsageWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::UsageWindow) {
    ui->setupUi(this);
}

UsageWindow::~UsageWindow() {
    delete ui;
}
