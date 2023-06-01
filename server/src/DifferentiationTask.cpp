#include "DifferentiationTask.hpp"

#include <cmath>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "ArithmeticTask.hpp"
#include "Exceptions.hpp"
#include "TaskInfo.hpp"

std::string replace_x_num(std::string func, const std::string& point) {
    size_t pos = func.find("x");
    while (pos != std::string::npos) {
        func.replace(pos, 1, point);
        pos = func.find("x");
    }

    return func;
}

namespace Tasks {

DifferentiationTask::DifferentiationTask(std::string expression, TaskTypes taskType) {
    Expression = std::move(expression);
    TaskType = taskType;
}

void DifferentiationTask::ParseData() {
    ;
    //для символьного и численного дифференцирования будут различные парсеры,
    //пока что один реализован внутри функции Numerical
}

std::string DifferentiationTask::Solve() {
    // ParseData();

    switch (TaskType) {
        case TaskTypes::DiffNum: {
            return DoubleToString(Numerical());
        }
        default: {
            throw TaskInvalidData("No such task type");
        }
    }
}

double DifferentiationTask::Numerical() {
    double step = 0.01;
    size_t end_pos = Expression.find(';');
    if (end_pos == std::string::npos) {
        throw TaskInvalidData("Wrong format");
    }
    std::string function = Expression.substr(0, end_pos);
    std::string point = Expression.substr(end_pos + 1, Expression.size() - end_pos - 1);

    std::regex digit("^[ ]*[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)[ ]*$");
    if (point.empty() || !(std::regex_match(point, digit))) {
        throw TaskInvalidData("No point provided");
    }

    double x_1 = std::stod(point);
    double x_0 = x_1 - step;
    double x_2 = x_1 + step;

    std::string point_0 = DoubleToString(x_0);
    std::string f0 = replace_x_num(function, point_0);

    std::string point_2 = DoubleToString(x_2);
    std::string f2 = replace_x_num(function, point_2);

    ArithmeticTask value0(f0, TaskTypes::Arithmetic);
    ArithmeticTask value2(f2, TaskTypes::Arithmetic);

    double result = (value2.Solve_d() - value0.Solve_d()) / (2 * step);
    return result;
}

}  // namespace Tasks