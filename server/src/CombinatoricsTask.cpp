#include "CombinatoricsTask.hpp"

#include <cmath>
#include <sstream>
#include <string>
#include <vector>

#include "Exceptions.hpp"

namespace Tasks {

CombinatoricsTask::CombinatoricsTask(const std::string expression, TaskTypes taskType) {
    Expression = std::move(expression);
    TaskType = taskType;
}

std::string CombinatoricsTask::Solve() {
    ParseData();

    switch (TaskType) {
        case TaskTypes::CombComb: {
            return std::to_string(Combinations());
        }
        case TaskTypes::CombRe: {
            return std::to_string(Reshuffle());
        }
        case TaskTypes::CombPlace: {
            return std::to_string(Placements());
        }
        case TaskTypes::CombPart: {
            return std::to_string(Partitioning());
        }
        default: {
            throw TaskInvalidData("Wrong task type");
        }
    }
}

int CombinatoricsTask::Placements() {
    int n = Numbers[1];
    int k = Numbers[0];

    if (k > n) {
        throw TaskInvalidData("n and k must be non-negative integers, and k must be less than or equal to n");
    }

    if (n / (n - k) > 14) {
        throw TaskInvalidData("Values of n and k are too high");
    }

    int result = 1;

    for (int i = 0; i < k; ++i) {
        result *= n - i;
    }

    return result;
}

int CombinatoricsTask::Reshuffle() {
    int n = Numbers[0];

    if (n > 14) {
        throw TaskInvalidData("The number must not be higher than 14");
    }

    int result = 1;

    for (int i = 2; i <= n; ++i) {
        result *= i;
    }

    return result;
}

int CombinatoricsTask::Partitioning() {
    int n = Numbers[0];

    if (n > 40) {
        throw TaskInvalidData("The number must not be higher than 40");
    }

    std::vector<int> partitions(n + 1, 0);

    partitions[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            partitions[j] += partitions[j - i];
        }
    }

    return partitions[n] - 1;
}

int CombinatoricsTask::Combinations() {
    int k = Numbers[0];
    int n = Numbers[1];

    if (k > n) {
        throw TaskInvalidData("k and n must be k <= n");
    }

    if (n > 50 || k > 50) {
        throw TaskInvalidData("Values of n and k are too high");
    }

    std::vector<std::vector<int>> table(n + 1, std::vector<int>(k + 1, 0));

    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= std::min(i, k); ++j) {
            if (j == 0 || j == i) {
                table[i][j] = 1;
            } else {
                table[i][j] = table[i - 1][j] + table[i - 1][j - 1];
            }
        }
    }

    return table[n][k];
}

void CombinatoricsTask::ParseData() {
    if (TaskType == TaskTypes::CombComb || TaskType == TaskTypes::CombPlace) {
        if (Expression.find_first_not_of("0123456789 ") != std::string::npos) {
            throw TaskInvalidData("Invalid Data");
        }

        std::istringstream iss(Expression);
        int num;

        while (iss >> num) {
            Numbers.push_back(num);
        }

        if (Numbers.size() != 2) {
            throw TaskInvalidData("Expected two positive integers separated by a space");
        }

    } else if (TaskType == TaskTypes::CombRe || TaskType == TaskTypes::CombPart) {
        if (Expression.find_first_not_of("0123456789 ") != std::string::npos) {
            throw TaskInvalidData("Invalid Data");
        }

        std::istringstream iss(Expression);
        int num;

        if (!(iss >> num)) {
            throw TaskInvalidData("Expected a positive integer");
        }

        Numbers.push_back(num);

        if (iss >> num) {
            throw TaskInvalidData("Expected only one positive integer");
        }

    } else {
        throw TaskInvalidData("Invalid task type");
    }
}

}  // namespace Tasks