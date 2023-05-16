
#include "ui_usagewindow.h"
#include "usagewindow.h"

UsageWindow::UsageWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::UsageWindow){
    ui->setupUi(this);
}

UsageWindow::~UsageWindow(){
    delete ui;
}
