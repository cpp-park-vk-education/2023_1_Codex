#pragma once

#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QObject>
#include <QSpinBox>
#include <QWidget>
#include <iostream>
#include <memory>

class MatrixInputForm : public QWidget {
   public:
    MatrixInputForm(bool isEQ = false, QWidget *parent = nullptr) : makeEq(isEQ), QWidget(parent) {
        std::cout << "makeEq = " << makeEq << std::endl;
        createLayout();
        connectSignals();
        updateMatrixSize();
    }

    int getRows() {
        return rowsSpinBox->value();
    }
    int getCols() {
        return colsSpinBox->value();
    }

    QVector<QVector<QLineEdit *>> getMatrixInputs() {
        return matrixInputs;
    }

    QVector<QLineEdit *> getEqualsInputs() {
        return equalsInputs;
    }

    std::shared_ptr<QGridLayout> getGridLayout() {
        return gridLayout;
    }

   private:
    std::shared_ptr<QGridLayout> gridLayout;
    std::shared_ptr<QSpinBox> rowsSpinBox;
    std::shared_ptr<QSpinBox> colsSpinBox;
    std::shared_ptr<QLabel> rowsLabel;
    std::shared_ptr<QLabel> colsLabel;
    QVector<QVector<QLineEdit *>> matrixInputs;
    QVector<QLineEdit *> equalsInputs;
    QLabel *additionalLabel;
    bool makeEq;

    void createLayout();
    void connectSignals();
    void updateMatrixSize();
};
