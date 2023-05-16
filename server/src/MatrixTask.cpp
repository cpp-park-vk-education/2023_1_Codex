#include "MatrixTask.hpp"

#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Exceptions.hpp"
#include "TaskInfo.hpp"

// Функция для умножения матрицы на вектор
std::vector<double> matrixVectorMultiply(const std::vector<std::vector<double>>& matrix,
                                         const std::vector<double>& vector) {
    int rows = matrix.size();
    int cols = matrix[0].size();
    std::vector<double> result(rows);

    for (int i = 0; i < rows; i++) {
        double sum = 0.0;
        for (int j = 0; j < cols; j++) {
            sum += matrix[i][j] * vector[j];
        }
        result[i] = sum;
    }

    return result;
}

// Функция для нормализации вектора
void normalizeVector(std::vector<double>& vector) {
    double magnitude = 0.0;
    int size = vector.size();

    for (int i = 0; i < size; i++) {
        magnitude += vector[i] * vector[i];
    }
    magnitude = std::sqrt(magnitude);

    for (int i = 0; i < size; i++) {
        vector[i] /= magnitude;
    }
}

namespace Tasks {

MatrixTask::MatrixTask(std::string expression, TaskTypes taskType) {
    Expression = std::move(expression);
    TaskType = taskType;
}

std::string MatrixTask::Solve() {
    ParseData();

    switch (TaskType) {
        case TaskTypes::MatrixDet: {
            return DoubleToString(Determinant());
        }

        case TaskTypes::MatrixT: {
            std::vector<std::vector<double>> newData = (Transpose());
            std::string result;
            for (size_t j = 0; j < cols; j++) {
                for (size_t i = 0; i < rows; ++i) {
                    result.append(DoubleToString(data[i][j]) + ' ');
                }
                result.append("/ ");
            }
            return result;
        }

        case TaskTypes::MatrixRank: {
            return DoubleToString(Rank());
        }

        case TaskTypes::MatrixNorm: {
            return DoubleToString(Norma());
        }

        case TaskTypes::MatrixEigen: {
            EigenValuesAndVectors();
            std::string result;
            for (int i = 0; i < eigenvalues.size(); i++) {
                result.append(DoubleToString(eigenvalues[i]) + " : [");
                for (int j = 0; j < eigenvectors[i].size(); j++) {
                    result.append(" " + DoubleToString(eigenvectors[i][j]));
                    if (j != eigenvectors[i].size() - 1) {
                        result.append(", ");
                    } else {
                        result.append(" ] ");
                    }
                }
            }
            return result;
        }

        default: {
            throw TaskInvalidData("Wrong task type");
        }
    }
}

void MatrixTask::ParseData() {
    if (Expression == "") {
        throw TaskInvalidData("No matrix given");
    }
    std::string lexem;
    std::stringstream ss(Expression);

    std::vector<double> line;
    unsigned i = 0;
    while (ss >> lexem) {
        if (lexem == "/") {
            if (i == 1) {
                cols = data[0].size();
            }
            if (i > 0 && line.size() != cols) {
                throw TaskInvalidData("Matrix should have equal number of elements in rows");
            }
            data.push_back(line);
            line.clear();

            i++;
        } else {
            line.push_back(std::stod(lexem));
        }
    }

    if (i == 1) {
        cols = data[0].size();
    }

    if (!line.empty()) {
        if (i > 0 && line.size() != cols) {
            throw TaskInvalidData("Matrix should have equal number of elements in rows");
        }
        data.push_back(line);
        line.clear();
        i++;
    }

    rows = data.size();
}

double MatrixTask::Determinant() {
    if (rows != cols) {
        throw TaskInvalidData("DimenssionMismatch");
    }
    return countDet(data, cols, rows);
}

double MatrixTask::countDet(std::vector<std::vector<double>> data, unsigned cols, unsigned rows) const {
    if (rows == 1) {
        return data[0][0];
    }
    if (rows == 2) {
        return data[0][0] * data[1][1] - data[0][1] * data[1][0];
    }

    double val = 0.0;
    size_t i = ROW_FOR_DECOMP;

    for (size_t j = 0; j < cols; j++) {
        //считаем миноры, разложенние по первой строке
        double det_m = countMinor(rows, cols, i, j);

        if ((i + j) % 2 == 0) {
            val += data[i][j] * det_m;
        } else {
            val -= data[i][j] * det_m;
        }
    }
    return val;
}

double MatrixTask::countMinor(size_t rows, size_t cols, size_t row, size_t col) const {
    size_t x = 0;
    std::vector<std::vector<double>> NewData(rows - 1, std::vector<double>(cols - 1, 0));
    for (size_t i = 0; i < rows; ++i) {
        if (i == row) {
            --x;
        } else {
            size_t y = 0;

            for (size_t j = 0; j < cols; ++j) {
                if (j == col) {
                    --y;
                } else {
                    NewData[x][y] = data[i][j];
                }
                ++y;
            }
        }
        ++x;
    }

    return countDet(NewData, cols - 1, rows - 1);
}

std::vector<std::vector<double>> MatrixTask::Transpose() const {
    std::vector<std::vector<double>> NewData(cols, std::vector<double>(rows, 0));

    for (size_t i = 0; i < cols; i++) {
        for (size_t j = 0; j < rows; j++) {
            NewData[i][j] = data[j][i];
        }
    }
    return NewData;
}

// Функция для вычисления ранга матрицы
int MatrixTask::Rank() {
    int rank = 0;
    int col;

    for (col = 0; col < cols; ++col) {
        int i;

        // Находим строку с ненулевым элементом в текущем столбце
        for (i = rank; i < rows; ++i) {
            if (data[i][col] != 0) break;
        }

        // Если такая строка найдена
        if (i < rows) {
            // Перемещаем строку с ненулевым элементом вверх
            std::swap(data[i], data[rank]);

            // Выполняем элементарные преобразования над матрицей
            performElementaryRowOperations(rank, col);

            // Увеличиваем ранг
            ++rank;
        }
    }
    return rank;
}

// Функция для выполнения элементарных преобразований над матрицей
void MatrixTask::performElementaryRowOperations(int row, int col) {
    double leadCoefficient = data[row][col];
    int rows = data.size();
    int cols = data[0].size();

    // Делаем ведущий элемент равным 1
    for (int j = col; j < cols; ++j) {
        data[row][j] /= leadCoefficient;
    }

    // Обновляем остальные строки
    for (int i = 0; i < rows; ++i) {
        if (i == row) continue;
        double rowMultiplier = data[i][col];

        for (int j = col; j < cols; ++j) {
            data[i][j] -= rowMultiplier * data[row][j];
        }
    }
}

double MatrixTask::Norma() {
    double result = 0;
    for (size_t j = 0; j < cols; j++) {
        for (size_t i = 0; i < rows; ++i) {
            result += data[i][j] * data[i][j];
        }
    }
    return sqrt(result);
}

void MatrixTask::EigenValuesAndVectors() {
    int size = data.size();
    eigenvectors.resize(size);
    eigenvalues.resize(size);

    // Начальное приближение для собственных векторов
    for (int i = 0; i < size; i++) {
        eigenvectors[i].resize(size);
        eigenvectors[i][i] = 1.0;
    }

    double epsilon = 1e-8;  // Порог сходимости
    double maxDiff = epsilon + 1.0;
    int maxIterations = 100;  // Максимальное количество итераций

    int iteration = 0;
    while (maxDiff > epsilon && iteration < maxIterations) {
        // Умножение матрицы на собственные векторы
        for (int i = 0; i < size; i++) {
            std::vector<double> result = matrixVectorMultiply(data, eigenvectors[i]);
            eigenvectors[i] = result;
        }

        // Нормализация собственных векторов
        for (int i = 0; i < size; i++) {
            normalizeVector(eigenvectors[i]);
        }

        // Вычисление собственных значений
        for (int i = 0; i < size; i++) {
            std::vector<double> result = matrixVectorMultiply(data, eigenvectors[i]);
            eigenvalues[i] = result[i];
        }
        // Проверка сходимости
        maxDiff = 0.0;
        for (int i = 0; i < size; i++) {
            std::vector<double> result = matrixVectorMultiply(data, eigenvectors[i]);
            for (int j = 0; j < size; j++) {
                double diff = std::abs(result[j] - eigenvalues[i] * eigenvectors[i][j]);
                if (diff > maxDiff) {
                    maxDiff = diff;
                }
            }
        }
        iteration++;
    }
}

}  // namespace Tasks