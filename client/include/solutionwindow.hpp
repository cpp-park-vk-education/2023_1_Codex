#pragma once

#include <QMainWindow>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QGridLayout>
#include <usagewindow.h>

QT_BEGIN_NAMESPACE
namespace Ui{ class SolutionWindow; }
QT_END_NAMESPACE

class SolutionWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit SolutionWindow(QWidget* parent = nullptr);
    ~SolutionWindow();
    QGridLayout* gridLayout;

private slots:
    void on_new_problem_button_clicked();
    void on_back_clicked();
    void on_aboutButton_clicked();
    void on_stepsButton_clicked();
    void on_chartButton_clicked();

private:
    Ui::SolutionWindow* ui;
    UsageWindow* usageWindow;
    double* predicted_values;
    int was_prediction = 0;

    std::string solution;
    std::string expression;


    QtCharts::QChartView* mChart;
    QList<QtCharts::QChartView*> m_charts;
};
