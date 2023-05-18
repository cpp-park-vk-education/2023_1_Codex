#include "EquationsTask.hpp"

#include <cmath>
#include <iomanip>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "Exceptions.hpp"
#include "TaskInfo.hpp"

namespace Tasks {

EquationsTask::EquationsTask(const std::string expression, TaskTypes taskType) {
    Expression = std::move(expression);
    TaskType = taskType;
}

std::string EquationsTask::Solve() {
    ParseData();

    switch (TaskType) {
        case TaskTypes::EqLin: {
            return DoubleToString(SimpleLinear());
        }
        case TaskTypes::EqSq: {
            std::vector<double> nums = Square();

            if (nums.size() == 2) {
                std::stringstream ss;
                ss << "x_1 = " << DoubleToString(nums[0]) << ", x_2 = " << DoubleToString(nums[1]);
                return ss.str();
            } else {
                std::stringstream ss;
                ss << "x = " << DoubleToString(nums[0]);
                return ss.str();
            }
        }
        case TaskTypes::EqPoly: {
            Polynomial();
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
        return -b / a;
    }
}

std::vector<double> EquationsTask::Square() {
    double a = Numbers[0];
    double b = Numbers[1];
    double c = Numbers[2];

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

void EquationsTask::Polynomial() {
    throw TaskInvalidData("Sorry, we are not yet able to solve this problem");
}

void EquationsTask::ParseData() {
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
    } else {
        throw TaskInvalidData("Invalid task type");
    }
}

}  // namespace Tasks
