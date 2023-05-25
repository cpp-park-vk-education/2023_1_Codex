#include <gtest/gtest.h>

#include <string>

#include "Exceptions.hpp"
#include "EqSystemsTask.hpp"
#include "TaskInfo.hpp"

// ------------------------- Метод Гаусса -------------------------------

TEST(EqSystemTest, BasicGaussEqSystemsCase) {
    ::Tasks::EqSystemTask task(
        "4 2 1 / 3 3 3 / 1 1 2 , 12 9 3",
        ::Tasks::TaskTypes::EqSGauss);  // до запятой матрица A, после запятой столбец свободных значений
    std::string actual = task.Solve();

    std::string expected = "x_1 = 3.00000, x_2 = 0.00000, x_3 = 0.00000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(EqSystemTest, InvalidDataGaussEqSystemsCaseNotNums) {
    ::Tasks::EqSystemTask task("4 2sd 1 / 3 3 3 / 1 1 2 , 12 9 3", ::Tasks::TaskTypes::EqSGauss);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EqSystemTest, InvalidDataGaussEqSystemsCaseWrongMatrix) {
    ::Tasks::EqSystemTask task("4 2 1  3 3 3  1 1 2 , 12 9 3", ::Tasks::TaskTypes::EqSGauss);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EqSystemTest, InvalidDataGaussEqSystemsCaseWrongVector) {
    ::Tasks::EqSystemTask task("4 2 1 / 3 3 3 / 1 1 2", ::Tasks::TaskTypes::EqSGauss);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EqSystemTest, ZeroDetGaussEqSystemsCase) {
    ::Tasks::EqSystemTask task("0 0 0 / 0 0 0 / 0 0 0 , 12 9 3",
                                ::Tasks::TaskTypes::EqSGauss);  // вырожденная матрица

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EqSystemTest, WrongShapeGaussEqSystemsCase) {
    ::Tasks::EqSystemTask task("0 2 4 / 1 2 / 3 4 5 , 12 9 3",
                               ::Tasks::TaskTypes::EqSGauss);  // Неверный размер матрицы

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EqSystemTest, ZerosGaussEqSystemsCase) {
    ::Tasks::EqSystemTask task("0 0 0 / 1 2 7 / 3 4 5 , 0 0 0",
                               ::Tasks::TaskTypes::EqSGauss);  // Нули на верхней строке

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EqSystemTest, NotSquareMatrixGaussEqSystemsCase) {
    ::Tasks::EqSystemTask task(
        "4 2 1 6 / 3 3 3 8 / 1 1 2 9 , 12 9 3",
        ::Tasks::TaskTypes::EqSGauss);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EqSystemTest, WrongVectorShapeGaussEqSystemsCase) {
    ::Tasks::EqSystemTask task(
        "4 2 1 / 3 3 3 / 1 1 2 , 12 9 3 7",
        ::Tasks::TaskTypes::EqSGauss);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// ------------------------- Метод Гаусса с выбором главного элемента -------------------------------

// Для всех методов используется единый парсер, поэтому в других методах имеет смысл проверять только правильность решений

TEST(EqSystemTest, BasicGaussMEqSystemsCase) {
    ::Tasks::EqSystemTask task(
        "4 2 1 / 3 3 3 / 1 1 2 , 12 9 3",
        ::Tasks::TaskTypes::EqSGaussM);  // до запятой матрица A, после запятой столбец свободных значений
    std::string actual = task.Solve();

    std::string expected = "x_1 = 3.00000, x_2 = 0.00000, x_3 = 0.00000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

// ------------------------- LU разложение -------------------------------

TEST(EqSystemTest, BasicLUEqSystemsCase) {
    ::Tasks::EqSystemTask task(
        "4 2 1 / 3 3 3 / 1 1 2 , 12 9 3",
        ::Tasks::TaskTypes::EqSLU);  // до запятой матрица A, после запятой столбец свободных значений
    std::string actual = task.Solve();

    std::string expected = "x_1 = 3.00000, x_2 = 0.00000, x_3 = 0.00000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}