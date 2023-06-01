#include "MatrixInputForm.hpp"
#include <iostream>
using namespace std;

void MatrixInputForm::createLayout() {
    gridLayout = std::make_shared<QGridLayout>(this);

    rowsLabel = std::make_shared<QLabel>("Rows:", this);
    rowsLabel->setAlignment(Qt::AlignCenter);
    rowsLabel->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
    gridLayout->addWidget(rowsLabel.get(), 0, 0, 1, 2, Qt::AlignCenter);

    rowsSpinBox = std::make_shared<QSpinBox>(this);
    rowsSpinBox->setAlignment(Qt::AlignCenter);
    rowsSpinBox->setMinimum(1);
    if (makeEq){
        std::cout<<"rowsSpinBox->setMaximum(4);\n";
        rowsSpinBox->setMaximum(4);
    }
    else{
        rowsSpinBox->setMaximum(7);
    }
    rowsSpinBox->setValue(3);
    rowsSpinBox->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
    gridLayout->addWidget(rowsSpinBox.get(), 0, 2, 1, 2, Qt::AlignCenter);

    colsLabel = std::make_shared<QLabel>("Columns:", this);
    colsLabel->setAlignment(Qt::AlignCenter);
    colsLabel->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
    gridLayout->addWidget(colsLabel.get(), 1, 0, 1, 2, Qt::AlignCenter);

    colsSpinBox = std::make_shared<QSpinBox>(this);
    colsSpinBox->setAlignment(Qt::AlignCenter);
    colsSpinBox->setMinimum(1);
    if (makeEq){
        colsSpinBox->setMaximum(4);
    }
    else{
        colsSpinBox->setMaximum(7);
    }
    colsSpinBox->setValue(3);
    colsSpinBox->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
    gridLayout->addWidget(colsSpinBox.get(), 1, 2, 1, 2, Qt::AlignCenter);


            // Create initial matrix inputs
    for (int row = 0; row < 3; ++row) {
        QVector<QLineEdit *> rowInputs;
        for (int col = 0; col < 3; ++col) {
            QLineEdit *lineEdit = new QLineEdit(this);
            lineEdit->setFixedSize(60, 30);
            lineEdit->setText("0");
            lineEdit->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
            lineEdit->setAlignment(Qt::AlignCenter);
            gridLayout->addWidget(lineEdit, row + 2, col, 1, 1, Qt::AlignCenter);
            rowInputs.append(lineEdit);
        }
        matrixInputs.append(rowInputs);
    }

    if (makeEq){
        // Создание лейбла
        additionalLabel = new QLabel("<html><head/><body><p><span style=\"font-size:30pt; vertical-align:sub;\">X =</span><span style=\"border-top:1px solid white;\"></span></p></body></html>", this);
        additionalLabel->setAlignment(Qt::AlignCenter);
        additionalLabel->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
        additionalLabel->setGeometry(0,0,60,30);
        gridLayout->addWidget(additionalLabel, rowsSpinBox->value()/2+2, colsSpinBox->value()+1, 1, 2, Qt::AlignCenter);

                // Создание дополнительной таблицы
        for (int row = 0; row < rowsSpinBox->value(); ++row) {
            QLineEdit *lineEdit = new QLineEdit(this);
            lineEdit->setFixedSize(60, 30);
            lineEdit->setText("0");
            lineEdit->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
            lineEdit->setAlignment(Qt::AlignCenter);
            gridLayout->addWidget(lineEdit, 2 + row, colsSpinBox->value()+4, 1, 1, Qt::AlignCenter);
            equalsInputs.append(lineEdit);
        }

    }


}

void MatrixInputForm::connectSignals() {
    connect(rowsSpinBox.get(), QOverload<int>::of(&QSpinBox::valueChanged), this, &MatrixInputForm::updateMatrixSize);
    connect(colsSpinBox.get(), QOverload<int>::of(&QSpinBox::valueChanged), this, &MatrixInputForm::updateMatrixSize);
}

void MatrixInputForm::updateMatrixSize() {
    int rows = rowsSpinBox->value();
    int cols = colsSpinBox->value();

            // Remove extra rows
    while (matrixInputs.size() > rows) {
        QVector<QLineEdit *> rowInputs = matrixInputs.last();
        for (QLineEdit *lineEdit : rowInputs) {
            gridLayout->removeWidget(lineEdit);
            delete lineEdit;
        }
        matrixInputs.removeLast();
    }

    while (equalsInputs.size() > rows) {
        QLineEdit* rowInputs = equalsInputs.last();
        gridLayout->removeWidget(rowInputs);
        delete rowInputs;
        equalsInputs.removeLast();
    }

            // Add new rows
    while (matrixInputs.size() < rows) {
        QVector<QLineEdit *> rowInputs;
        for (int col = 0; col < cols; ++col) {
            QLineEdit *lineEdit = new QLineEdit(this);
            lineEdit->setFixedSize(60, 30);
            lineEdit->setText("0");
            lineEdit->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
            lineEdit->setAlignment(Qt::AlignCenter);
            gridLayout->addWidget(lineEdit, matrixInputs.size() + 2, col);
            rowInputs.append(lineEdit);
        }
        matrixInputs.append(rowInputs);
    }

            // Update number of columns for existing rows
    for (int row = 0; row < rows; ++row) {
        QVector<QLineEdit *> rowInputs = matrixInputs[row];
        // Remove extra columns
        while (rowInputs.size() > cols) {
            QLineEdit *lineEdit = rowInputs.last();
            gridLayout->removeWidget(lineEdit);
            delete lineEdit;
            rowInputs.removeLast();
        }
        // Add new columns
        while (rowInputs.size() < cols) {
            QLineEdit *lineEdit = new QLineEdit(this);
            lineEdit->setFixedSize(60, 30);
            lineEdit->setText("0");
            lineEdit->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
            lineEdit->setAlignment(Qt::AlignCenter);
            gridLayout->addWidget(lineEdit, row + 2, rowInputs.size());
            rowInputs.append(lineEdit);
        }
        matrixInputs[row] = rowInputs;
    }

    if (cols>5){
        gridLayout->addWidget(rowsLabel.get(), 0, 0, 1, 2, Qt::AlignCenter);
        gridLayout->addWidget(rowsSpinBox.get(), 0, 2, 1, 2, Qt::AlignCenter);
        gridLayout->addWidget(colsLabel.get(), 0, 4, 1, 2, Qt::AlignCenter);
        gridLayout->addWidget(colsSpinBox.get(), 0, 6, 1, 2, Qt::AlignCenter);
        this->update();
    }
    else{
        gridLayout->addWidget(rowsLabel.get(), 0, 0, 1, 2, Qt::AlignCenter);
        gridLayout->addWidget(rowsSpinBox.get(), 0, 2, 1, 2, Qt::AlignCenter);
        gridLayout->addWidget(colsLabel.get(), 1, 0, 1, 2, Qt::AlignCenter);
        gridLayout->addWidget(colsSpinBox.get(), 1, 2, 1, 2, Qt::AlignCenter);
        this->update();
    }

    if (makeEq){
        // Создание лейбла
        delete(additionalLabel);
        additionalLabel = new QLabel("<html><head/><body><p><span style=\"font-size:30pt; vertical-align:sub;\">X =</span><span style=\"border-top:1px solid white;\"></span></p></body></html>", this);
        additionalLabel->setAlignment(Qt::AlignCenter);
        additionalLabel->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
        additionalLabel->setGeometry(0,0,60,30);
        gridLayout->addWidget(additionalLabel, rowsSpinBox->value()/2+2, colsSpinBox->value()+1, 1, 2, Qt::AlignCenter);

        while (equalsInputs.size() < rows) {
                QLineEdit *lineEdit = new QLineEdit(this);
                lineEdit->setFixedSize(60, 30);
                lineEdit->setText("0");
                lineEdit->setStyleSheet("color: white; font-size: 20px; font: \"Century Gothic\"");
                lineEdit->setAlignment(Qt::AlignCenter);
                gridLayout->addWidget(lineEdit, 2 + equalsInputs.size(), colsSpinBox->value()+4, 1, 1, Qt::AlignCenter);

            equalsInputs.append(lineEdit);
        }
          }

}
