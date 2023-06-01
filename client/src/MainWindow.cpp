#include "MainWindow.hpp"

#include <QFont>
#include <QFontDatabase>

#include "UI_MainWindow.hpp"

MainWindow::MainWindow(const Client::ClientSPtr& client, QWidget* parent)
    : m_client(client), QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    setFixedSize(800, 600);

    problemTypeWindow = std::make_shared<ProblemTypeWindow>(client);
    connect(this, &MainWindow::clientAvailable, problemTypeWindow.get(), &ProblemTypeWindow::setClient);
    usageWindow = std::make_shared<UsageWindow>();

    // подключаем к слоту запуска главного окна по кнопке во втором окне
    connect(problemTypeWindow.get(), &ProblemTypeWindow::openMainWindow, this, &MainWindow::show);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::setClient(const Client::ClientSPtr& client) {
    m_client = client;
}

void MainWindow::on_usageButton_clicked() {
    usageWindow->show();  // Показываем второе окно
    // this->close();    // Закрываем основное окно
}

void MainWindow::on_startButton_clicked() {
    emit clientAvailable(m_client);
    problemTypeWindow->show();  // Показываем третье окно
    this->close();              // Закрываем основное окно
}
