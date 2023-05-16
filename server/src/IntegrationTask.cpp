#include "IntegrationTask.hpp"

#include <string>
#include <vector>
#include <sstream>

#include "taskInfo.hpp"
#include "exceptions.hpp"

#include "ArithmeticTask.hpp"
#include "ArithmeticTask.cpp"

namespace Tasks {

    IntegrationTask::IntegrationTask(const std::string expression, TaskTypes taskType) {
        Expression = std::move(expression);
        TaskType = taskType;
    }

    double IntegrationTask::f(std::string expr, double x) {
        std::string modifiedExpr = expr;
        size_t pos = modifiedExpr.find('x');

        // Заменяем символ 'x' на значение x
        while (pos != std::string::npos) {
            modifiedExpr.replace(pos, 1, std::to_string(x));
            pos = modifiedExpr.find('x', pos + 1);
        }

        // Вычисляем значение выражения
        Tasks::ArithmeticTask task(modifiedExpr, Tasks::TaskTypes::Arithmetic);

        double result = std::stod(task.Solve());

        return result;
    }

    std::string IntegrationTask::Solve() {
        ParseData();

        switch (TaskType) {
            case TaskTypes::IntegNewton: {
                return DoubleToString(NewtonCotes());
            }
            case TaskTypes::IntegSimpson: {
                return DoubleToString(Simpson());
            }
            case TaskTypes::IntegTrapez: {
                return DoubleToString(Trapezoid());
            }
            default: {
                throw TaskInvalidData("Wrong task type");
            }
        }
    }

    double IntegrationTask::NewtonCotes() { // формула средних
        // Расчет шага интегрирования
        double h = (b - a) / n;  // Шаг интегрирования

        double sum = 0.0;
        for (int i = 0; i < n; i++) {
            double x = a + (i + 0.5) * h;  // Середина интервала
            sum += f(expr, x);  // Суммирование значений функции в серединах интервалов
        }

        return h * sum;
    }

    double IntegrationTask::Simpson() {
        double h = (b - a) / n; // Шаг интегрирования

        double sum = f(expr, a) + f(expr, b);

        for (int i = 1; i < n; i++) {
            double x = a + i * h;

            if (i % 2 == 0) {
                sum += 2 * f(expr, x);
            } else {
                sum += 4 * f(expr, x);
            }
        }

        return (h / 3) * sum;
    }

    double IntegrationTask::Trapezoid() {
        double h = (b - a) / n; // Вычисляем шаг интегрирования
        double sum = 0.0;

        // Вычисляем значения функции в узлах
        double fa = f(expr, a);
        double fb = f(expr, b);

        // Вычисляем сумму площадей трапеций
        for (int i = 1; i < n; i++) {
            double x = a + i * h;
            sum += f(expr, x);
        }

        // Вычисляем итоговое значение интеграла
        double integral = (h / 2) * (fa + 2 * sum + fb);
        return integral;
    }

    void IntegrationTask::ParseData() {
        // Разделение строки на три части
        std::istringstream iss(Expression);
        std::string part1, part2, part3;
        if (!std::getline(iss, part1, ',') || !std::getline(iss, part2, ',') || !std::getline(iss, part3)) {
            throw TaskInvalidData("Incorrect expression format");
        }

        expr = part1;

        std::istringstream bounds_ss(part2 + " " + part3);

        if (!(bounds_ss >> a) || !(bounds_ss >> b) || !(bounds_ss >> n)) {
            throw TaskInvalidData("Error: Incorrect values for boundaries or number of nodes.");
        }

        // Проверка корректности границ интегрирования и количества узлов
        if (n < 0) {
            throw TaskInvalidData("Error: The number of nodes cannot be negative.");
        } else if (a > b) {
            throw TaskInvalidData("Error: The value of 'a' cannot be greater than the value of 'b'.");
        }
    }

}
