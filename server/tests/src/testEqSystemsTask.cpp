#include <gtest/gtest.h>

#include <string>

#include "Exceptions.hpp"
#include "IntegrationsTask.hpp"
#include "TaskInfo.hpp"

// ------------------------- Метод Гаусса -------------------------------

TEST(EqSystemTest, BasicGaussEqSystemsCase) {
    ::Tasks::EqSystemsTask task(
        "4 2 1 / 3 3 3 / 1 1 2 , 12 9 3",
        ::Tasks::TaskTypes::EqSGauss);  // до запятой матрица A, после запятой столбец свободных значений
    std::string actual = task.Solve();

    std::string expected = "x_1 = 3, x_2 = 0, x_3 = 0";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(EqSystemTest, InvalidDataGaussEqSystemsCase1) {
    ::Tasks::EqSystemsTask task("4 2sd 1 / 3 * e 3 3 / 1 1 2 , 12 9 3", ::Tasks::TaskTypes::EqSGauss);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EqSystemTest, InvalidDataGaussEqSystemsCase2) {
    ::Tasks::EqSystemsTask task("4 2 1  3 3 3  1 1 2 , 12 9 3", ::Tasks::TaskTypes::EqSGauss);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EqSystemTest, InvalidDataGaussEqSystemsCase3) {
    ::Tasks::EqSystemsTask task("4 2 1 / 3 3 3 / 1 1 2", ::Tasks::TaskTypes::EqSGauss);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EqSystemTest, ZeroDetGaussEqSystemsCase) {
    ::Tasks::EqSystemsTask task("0 0 0 / 0 0 0 / 0 0 0 , 12 9 3",
                                ::Tasks::TaskTypes::EqSGauss);  // вырожденная матрица

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// ------------------------- Метод Гаусса с выбором главного элемента -------------------------------

TEST(EqSystemTest, BasicGaussMEqSystemsCase) {
    ::Tasks::EqSystemsTask task(
        "4 2 1 / 3 3 3 / 1 1 2 , 12 9 3",
        ::Tasks::TaskTypes::EqSGaussM);  // до запятой матрица A, после запятой столбец свободных значений
    std::string actual = task.Solve();

    std::string expected = "x_1 = 3, x_2 = 0, x_3 = 0";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(EqSystemTest, InvalidDataGaussMEqSystemsCase1) {
    ::Tasks::EqSystemsTask task("4 2sd 1 / 3 * e 3 3 / 1 1 2 , 12 9 3", ::Tasks::TaskTypes::EqSGaussM);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EqSystemTest, InvalidDataGaussMEqSystemsCase2) {
    ::Tasks::EqSystemsTask task("4 2 1  3 3 3  1 1 2 , 12 9 3", ::Tasks::TaskTypes::EqSGaussM);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EqSystemTest, InvalidDataGaussMEqSystemsCase3) {
    ::Tasks::EqSystemsTask task("4 2 1  3 3 3  1 1 2", ::Tasks::TaskTypes::EqSGaussM);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EqSystemTest, ZeroDetGaussMEqSystemsCase) {
    ::Tasks::EqSystemsTask task("0 0 0 / 0 0 0 / 0 0 0 , 12 9 3",
                                ::Tasks::TaskTypes::EqSGaussM);  // вырожденная матрица

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// ------------------------- LU разложение -------------------------------

TEST(EqSystemTest, BasicLUEqSystemsCase) {
    ::Tasks::EqSystemsTask task(
        "4 2 1 / 3 3 3 / 1 1 2 , 12 9 3",
        ::Tasks::TaskTypes::EqSLU);  // до запятой матрица A, после запятой столбец свободных значений
    std::string actual = task.Solve();

    std::string expected = "x_1 = 3, x_2 = 0, x_3 = 0";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(EqSystemTest, InvalidDataLUEqSystemsCase) {
    ::Tasks::EqSystemsTask task("4 2sd 1 / 3 * e 3 3 / 1 1 2 , 12 9 3", ::Tasks::TaskTypes::EqSLU);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EqSystemTest, ZeroDetLUEqSystemsCase) {
    ::Tasks::EqSystemsTask task("0 0 0 / 0 0 0 / 0 0 0 , 12 9 3",
                                ::Tasks::TaskTypes::EqSLU);  // вырожденная матрица

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EqSystemTest, NonQuadLUEqSystemsCase) {
    ::Tasks::EqSystemsTask task("1 2 3 4 / 1 2 3 4 / 1 2 3 4 , 12 9 3",
                                ::Tasks::TaskTypes::EqSLU);  // матрица не квадратная

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}