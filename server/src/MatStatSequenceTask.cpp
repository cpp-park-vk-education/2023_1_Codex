#include "MatStatSequenceTask.hpp"

#include <cmath>
#include <sstream>
#include <string>
#include <vector>

#include "Exceptions.hpp"
#include "TaskInfo.hpp"

namespace Tasks {

constexpr double EPSILON = 0.000001;

MatStatSequenceTask::MatStatSequenceTask(std::string expression, TaskTypes taskType) : Degree(0.0) {
    Expression = std::move(expression);
    TaskType = taskType;
}

std::string MatStatSequenceTask::Solve() {
    ParseData();

    switch (TaskType) {
        case TaskTypes::MatStatSeqInitMoment: {
            return std::to_string(InitialMoment(Degree));
        }
        case TaskTypes::MatStatSeqCentralMoment: {
            return std::to_string(CentralMoment(Degree));
        }
        case TaskTypes::MatStatSeqAsymmetry: {
            return std::to_string(Asymmetry());
        }
        case TaskTypes::MatStatSeqExcess: {
            return std::to_string(Excess());
        }
        case TaskTypes::MatStatSeqQuantile: {
            return std::to_string(Quantile());
        }
        default: {
            throw TaskInvalidData("Wrong task type");
        }
    }
}

void MatStatSequenceTask::ParseData() {
    std::istringstream data(Expression);
    bool wasDegreeSym = false;
    bool wasDegree = false;

    while (!data.eof()) {
        std::string var;
        getline(data, var, ' ');

        // Check numbers' end
        if (var == "/") {
            wasDegreeSym = true;
            continue;
        }

        double num = 0.0;
        try {
            num = std::stod(var);
        } catch (...) {
            // Error if read string isn't double
            throw TaskInvalidData("There are non-numeric symbols in expression");
        }

        // Save read number in vector or as Degree
        if (wasDegreeSym) {
            Degree = num;
            // if (!data.eof()) {
            if (wasDegree) {
                // Error if Degree isn't only one number
                throw TaskInvalidData("Degree must be only one number");
            }
            wasDegree = true;
        } else {
            Numbers.push_back(num);
        }
    }
}

double MatStatSequenceTask::InitialMoment(double degree) {
    // Degree must be > 0 and be integer number
    if (degree < 1.0 || degree - static_cast<int>(degree) < EPSILON) {
        throw TaskInvalidData("Wrong degree of initial moment");
    }
    double initMoment = 0.0;
    for (double num : Numbers) {
        initMoment += std::pow(num, static_cast<int>(degree)) / Numbers.size();
    }
    return initMoment;
}

double MatStatSequenceTask::CentralMoment(double degree) {
    // Degree must be > 1 and be integer number
    if (degree < 2.0 || degree - static_cast<int>(degree) < EPSILON) {
        throw TaskInvalidData("Wrong degree of central moment");
    }
    double centralMoment = 0.0;

    double mathExpectation = InitialMoment(1);
    for (double num : Numbers) {
        centralMoment += std::pow(num - mathExpectation, static_cast<int>(degree)) / Numbers.size();
    }
    return centralMoment;
}

double MatStatSequenceTask::Asymmetry() {
    double std = std::pow(CentralMoment(2), 0.5);
    double thirdCM = CentralMoment(3);

    return thirdCM / std::pow(std, 3);
}

double MatStatSequenceTask::Excess() {
    double variety = CentralMoment(2);
    double fourthCM = CentralMoment(4);

    return fourthCM / std::pow(variety, 2) - 3;
}

double MatStatSequenceTask::Quantile() {
    if (Degree < 0.0 || Degree > 1.0) {
        throw TaskInvalidData("Wrong quantile");
    }

    int needIndex = static_cast<int>(Numbers.size() * Degree) - 1;
    if (needIndex == -1) {
        return Numbers[0] - 0.5;
    }
    // Check case of Numbers[needIndex] is last elem
    double delta = Numbers.size() == needIndex + 1 ? 1 : Numbers[needIndex + 1] - Numbers[needIndex];

    return Numbers[needIndex] + delta / 2;
}

}  // namespace Tasks
