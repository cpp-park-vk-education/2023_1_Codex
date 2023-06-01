#include "EquationsTask.hpp"

#include <cmath>
#include <sstream>
#include <string>
#include <vector>

#include "Exceptions.hpp"
#include "ArithmeticTask.hpp"
#include "DifferentiationTask.hpp"

namespace Tasks {

EquationsTask::EquationsTask(const std::string expression, TaskTypes taskType) {
    Expression = std::move(expression);
    TaskType = taskType;
}

std::string EquationsTask::Solve() {
    ParseData();

    switch (TaskType) {
        case TaskTypes::EqLin: {
            return "x = " + DoubleToString(SimpleLinear());
        }
        case TaskTypes::EqSq: {
            std::vector<double> nums = Square();

            if (nums.size() == 2) {
                return "x_1 = " + DoubleToString(nums[0]) + ", x_2 = " + DoubleToString(nums[1]);
            } else {
                return "x = " + DoubleToString(nums[0]);
            }
        }
        case TaskTypes::EqPoly: {
            return "x = " + DoubleToString(Polynomial());
        }
        default: {
            throw TaskInvalidData("Wrong task type");
        }
    }
}

double EquationsTask::SimpleLinear() {
    double a = Numbers[0];
    double b = Numbers[1];

    if (a == 0) {
        if (b == 0) {
            throw TaskInvalidData("The equation has infinitely many solutions");
        } else {
            throw TaskInvalidData("The equation has no solutions");
        }
    } else {
        return - b / a;
    }
}

std::vector<double> EquationsTask::Square() {
    double a = Numbers[0];
    double b = Numbers[1];
    double c = Numbers[2];

    if (a == 0) {
        throw TaskInvalidData("Divide by zero");
    }

    double discriminant = b * b - 4 * a * c;

    std::vector<double> result;

    if (discriminant > 0) {
        double root1 = (-b + sqrt(discriminant)) / (2 * a);
        double root2 = (-b - sqrt(discriminant)) / (2 * a);

        result.push_back(root1);
        result.push_back(root2);

    } else if (discriminant == 0) {
        double root = -b / (2 * a);

        result.push_back(root);

    } else {
        throw TaskInvalidData("The equation has no valid roots");
    }

    return result;
}

double EquationsTask::Polynomial() { // " x ^ 4 - 1 , 1 , 100" функция, начальное приближение, итерации
    double x_0 = Numbers[0];
    double max_iter = Numbers[1];

    double eps = 1e-6;

    size_t iter_count = 0;
    double error = 1.0;

    while (error > eps && iter_count < max_iter) {
        double f_val = get_f_x(expr, x_0);
        double f_derivative_val = get_f_derivative(expr, x_0);

        if (f_derivative_val == 0) {
            throw TaskInvalidData("The derivative is zero. Newton's method is not applicable.");
        }

        double x_next = x_0 - f_val / f_derivative_val;
        error = std::abs(x_next - x_0);
        x_0 = x_next;
        iter_count++;
    }

    if (iter_count == max_iter) {
        throw TaskInvalidData("The maximum number of iterations has been reached. No solution has been found.");
    }

    return x_0;
}

double EquationsTask::get_f_x(std::string expr, double x) {
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

double EquationsTask::get_f_derivative(std::string expr, double x) { // 12 * x ^ 2 + sin ( x ) - 6  ; 2
    std::string modifiedExpr = expr + " ; " + std::to_string(x);

    // Находим производную
    Tasks::DifferentiationTask task(modifiedExpr, Tasks::TaskTypes::DiffNum);

    double result = std::stod(task.Solve());

    return result;
}

void EquationsTask::ParseData() {
    Numbers.clear();
    if (TaskType == TaskTypes::EqSq) {
        std::istringstream ss(Expression);
        double num;

        while (ss >> num) {
            if (ss.fail()) {
                throw TaskInvalidData("Expected doubles separated by a space");
            }
            Numbers.push_back(num);
        }

        if (Numbers.size() != 3) {
            throw TaskInvalidData("Expected three doubles separated by a space");
        }
    } else if (TaskType == TaskTypes::EqLin) {
        std::istringstream ss(Expression);
        double num;

        while (ss >> num) {
            if (ss.fail()) {
                throw TaskInvalidData("Expected doubles separated by a space");
            }
            Numbers.push_back(num);
        }

        if (Numbers.size() != 2) {
            throw TaskInvalidData("Expected three doubles separated by a space");
        }
    } else if (TaskType == TaskTypes::EqPoly) {
        std::istringstream iss(Expression);
        std::string part1, part2, part3;
        if (!std::getline(iss, part1, ',') || !std::getline(iss, part2, ',') || !std::getline(iss, part3)) {
            throw TaskInvalidData("Incorrect expression format");
        }

        expr = part1;

        if ((part2.find_first_not_of("0123456789.- ") != std::string::npos) || (part3.find_first_not_of("0123456789.- ") != std::string::npos)) {
            throw TaskInvalidData("Invalid Data");
        }

        double x_0;
        double node_count;

        std::istringstream part2s(part2);

        if (!(part2s >> x_0)) {
            throw TaskInvalidData("Expected a positive integer");
        }

        if (part2s >> node_count) {
            throw TaskInvalidData("Expected only one positive integer");
        }

        std::istringstream part3s(part3);

        int max_iter;

        if (!(part3s >> max_iter)) {
            throw TaskInvalidData("Expected a positive integer");
        }

        if (part3s >> node_count) {
            throw TaskInvalidData("Expected only one positive integer");
        }

        if (max_iter < 0) {
            throw TaskInvalidData("Error: The number of nodes cannot be negative.");
        }

        Numbers.push_back(x_0);
        Numbers.push_back(max_iter);

    } else {
        throw TaskInvalidData("Invalid task type");
    }
}

}  // namespace Tasks
