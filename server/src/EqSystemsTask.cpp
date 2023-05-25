#include "EqSystemsTask.hpp"

#include <sstream>
#include <string>
#include <vector>

#include "Exceptions.hpp"

namespace Tasks {

EqSystemTask::EqSystemTask(const std::string expression, TaskTypes taskType) {
    Expression = std::move(expression);
    TaskType = taskType;
}

std::string EqSystemTask::VectorToString(const std::vector<double>& nums) {
    std::stringstream ss;
    std::string result;
    int size = nums.size();

    for (int i = 0; i < size; ++i) {
        double value = nums[i];

        if (value == 0.0) {
            value = 0.0;
        }

        ss << "x_" << (i + 1) << " = " << DoubleToString(value);

        if (i < size - 1) {
            ss << ", ";
        }
    }

    result = ss.str();
    return result;
}

void EqSystemTask::ParseData() {
    if (Expression.find_first_not_of("0123456789./,- ") != std::string::npos) {
        throw TaskInvalidData("Invalid Data");
    }

    std::istringstream is(Expression);
    std::string part1, part2;

    if (!std::getline(is, part1, ',') || !std::getline(is, part2)) {
        throw TaskInvalidData("Incorrect expression format");
    }

    std::istringstream prt1(part1);
    std::string line;

    while (std::getline(prt1, line, '/')) {
        std::vector<double> row;
        std::istringstream line_stream(line);
        std::string num_str;

        while (line_stream >> num_str) {
            try {
                double num = std::stod(num_str);
                row.push_back(num);
            } catch (const std::exception& e) {
                throw TaskInvalidData("Error parsing number");
            }
        }
        A.push_back(row);
    }

    // Check if the matrix is square
    if (!A.empty() && A.size() != A[0].size()) {
        throw TaskInvalidData("Error: Matrix is not square");
    }

    std::istringstream prt2(part2);
    double num;

    while (prt2 >> num) {
        if (num < 0) {
            throw TaskInvalidData("Expected positive doubles");
        }
        B.push_back(num);
    }

    if (B.size() != A.size()) {
        throw TaskInvalidData("A and B must have the same shape");
    }
}

std::string EqSystemTask::Solve() {
    ParseData();

    switch (TaskType) {
        case TaskTypes::EqSGauss: {
            return VectorToString(Gaussian());
        }
        case TaskTypes::EqSGaussM: {
            return VectorToString(GaussianMainEl());
        }
        case TaskTypes::EqSLU: {
            return VectorToString(LU());
        }
        default: {
            throw TaskInvalidData("Wrong task type");
        }
    }
}

std::vector<double> EqSystemTask::LU() {
    size_t n = A.size();

    for (size_t i = 0; i < n; ++i) {
        if (A[i][i] == 0.0) {
            throw TaskInvalidData("Singular matrix");
        }
    }

    std::vector<std::vector<double>> L(n, std::vector<double>(n, 0.0));
    std::vector<std::vector<double>> U(n, std::vector<double>(n, 0.0));

    for (size_t i = 0; i < n; ++i) {
        for (size_t k = i; k < n; ++k) {
            double sum = 0.0;
            for (size_t j = 0; j < i; ++j) {
                sum += L[i][j] * U[j][k];
            }
            U[i][k] = A[i][k] - sum;
        }

        for (size_t k = i; k < n; ++k) {
            if (i == k) {
                L[i][i] = 1.0;
            } else {
                double sum = 0.0;
                for (size_t j = 0; j < i; ++j) {
                    sum += L[k][j] * U[j][i];
                }
                L[k][i] = (A[k][i] - sum) / U[i][i];
            }
        }
    }

    std::vector<double> c(n, 0.0);

    for (size_t i = 0; i < n; ++i) {
        double sum = 0.0;
        for (size_t j = 0; j < i; ++j) {
            sum += L[i][j] * c[j];
        }
        c[i] = B[i] - sum;
    }

    std::vector<double> x(n, 0.0);

    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (size_t j = i + 1; j < n; ++j) {
            sum += U[i][j] * x[j];
        }
        x[i] = (c[i] - sum) / U[i][i];
    }

    return x;
}

std::vector<double> EqSystemTask::GaussianMainEl() {
    // Создаем копии исходных векторов
    std::vector<std::vector<double>> augmentedMatrix = A;
    std::vector<double> augmentedVector = B;

    const int n = augmentedVector.size();

    // Прямой ход
    for (int j = 0; j < n; ++j) {
        int maxRow = j;
        double maxElement = augmentedMatrix[j][j];
        for (int i = j + 1; i < n; ++i) {
            if (augmentedMatrix[i][j] > maxElement) {
                maxElement = augmentedMatrix[i][j];
                maxRow = i;
            }
        }

        std::swap(augmentedMatrix[j], augmentedMatrix[maxRow]);
        std::swap(augmentedVector[j], augmentedVector[maxRow]);

        // Нормализуем текущую строку j
        double pivot = augmentedMatrix[j][j];
        if (pivot == 0) {
            throw TaskInvalidData("Matrix A is singular");
        }
        for (int k = j; k < n; ++k) {
            augmentedMatrix[j][k] /= pivot;
        }
        augmentedVector[j] /= pivot;

        // Вычитаем текущую строку j из остальных строк
        for (int i = j + 1; i < n; ++i) {
            double factor = augmentedMatrix[i][j];
            for (int k = j; k < n; ++k) {
                augmentedMatrix[i][k] -= factor * augmentedMatrix[j][k];
            }
            augmentedVector[i] -= factor * augmentedVector[j];
        }
    }

    // Обратный ход
    std::vector<double> solution(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i + 1; j < n; ++j) {
            sum += augmentedMatrix[i][j] * solution[j];
        }
        solution[i] = augmentedVector[i] - sum;
    }

    return solution;
}

std::vector<double> EqSystemTask::Gaussian() {
    std::vector<std::vector<double>> matrixA = A;
    std::vector<double> vectorB = B;

    const int n = matrixA.size();

    // Прямой ход метода Гаусса
    for (int i = 0; i < n - 1; ++i) {
        // Проверка на ноль главного элемента
        if (matrixA[i][i] == 0) {
            throw TaskInvalidData("Zero pivot encountered. The system may not have a unique solution.");
        }

        for (int j = i + 1; j < n; ++j) {
            const double factor = matrixA[j][i] / matrixA[i][i];

            for (int k = i; k < n; ++k) {
                matrixA[j][k] -= factor * matrixA[i][k];
            }

            vectorB[j] -= factor * vectorB[i];
        }
    }

    // Обратный ход метода Гаусса
    std::vector<double> solution(n);

    for (int i = n - 1; i >= 0; --i) {
        double sum = 0.0;

        for (int j = i + 1; j < n; ++j) {
            sum += matrixA[i][j] * solution[j];
        }

        solution[i] = (vectorB[i] - sum) / matrixA[i][i];
    }

    return solution;
}
}  // namespace Tasks
