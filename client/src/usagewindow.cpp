#include "ui_usagewindow.hpp"
#include "usagewindow.hpp"

UsageWindow::UsageWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::UsageWindow){
    ui->setupUi(this);
}

UsageWindow::~UsageWindow(){
    delete ui;
}
