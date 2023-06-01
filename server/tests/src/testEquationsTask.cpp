#include <gtest/gtest.h>

#include <string>

#include "Exceptions.hpp"
#include "EquationsTask.hpp"

#include "TaskInfo.hpp"
#include "ArithmeticTask.hpp"
#include "DifferentiationTask.hpp"


// ------------------------- Линейные уравнения -------------------------------

TEST(EquationsTest, BasicLinearEquationsCase) {
    ::Tasks::EquationsTask task("4 -3", ::Tasks::TaskTypes::EqLin);  // линейное уравнение имеет вид a * x + b = 0
    std::string actual = task.Solve();

    std::string expected = "x = 0.75000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(EquationsTest, InvalidDataEquationsCaseFullEquation) {
    ::Tasks::EquationsTask task("3 * x = 3", ::Tasks::TaskTypes::EqLin);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, DivideByZeroEquationsCase) {
    ::Tasks::EquationsTask task("0 0", ::Tasks::TaskTypes::EqLin);  // Деление на ноль

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataEquationsEmptyString) {
    ::Tasks::EquationsTask task("", ::Tasks::TaskTypes::EqLin);  // Пустая строка

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataEquationsNotNums) {
    ::Tasks::EquationsTask task("4sd 1", ::Tasks::TaskTypes::EqLin);  // Не числа

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataEquationsWrongAmount) {
    ::Tasks::EquationsTask task("1 2 3", ::Tasks::TaskTypes::EqLin);  // Неверное количество аргументов

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// ------------------------- Квадратные уравнения -------------------------------

TEST(EquationsTest, BasicSquareEquationsCase) {
    ::Tasks::EquationsTask task("4 6 0", ::Tasks::TaskTypes::EqSq);
    std::string actual = task.Solve();

    std::string expected = "x_1 = 0.00000, x_2 = -1.50000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(EquationsTest, BasicSquareOneRootEquationsCase) {
    ::Tasks::EquationsTask task("4 -4 1", ::Tasks::TaskTypes::EqSq);
    std::string actual = task.Solve();

    std::string expected = "x = 0.50000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(EquationsTest, InvalidDataSqEquationsCaseFullEquation) {
    ::Tasks::EquationsTask task("4 * x ^ 2 - 5 * x + 7 = 0", ::Tasks::TaskTypes::EqSq);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataSqEquationsCaseWrongNodes) {
    ::Tasks::EquationsTask task("4*x ^2- 6*x",
                                ::Tasks::TaskTypes::EqSq);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, DivideByZeroSqEquations) {
    ::Tasks::EquationsTask task("0 0 0", ::Tasks::TaskTypes::EqSq);  // Деление ноль

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, DLessThanZeroSqEquationsCase) {
    ::Tasks::EquationsTask task("2 1 5",
                                ::Tasks::TaskTypes::EqSq);  // Дискриминант меньше нуля

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, NotNumsSqEquationsCase) {
    ::Tasks::EquationsTask task("2a -6e 5",
                                ::Tasks::TaskTypes::EqSq);  // Не числа

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, WrongAmountSqEquationsCase) {
    ::Tasks::EquationsTask task("2 5",
                                ::Tasks::TaskTypes::EqSq);  // Неверное количество аргументов

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, EmptyStringSqEquationsCase) {
    ::Tasks::EquationsTask task("",
                                ::Tasks::TaskTypes::EqSq);  // Пустая строка

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// ------------------------- Полиномиальные уравнения -------------------------------

TEST(EquationsTest, BasicPolyEquationsCase) {
    ::Tasks::EquationsTask task("x - 1 , -4 , 100", ::Tasks::TaskTypes::EqPoly); // " x ^ 4 - 1 , 1 , 100" функция, начальное приближение, итерации
    std::string actual = task.Solve();

    std::string expected = "x = 1.00000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(EquationsTest, BasicPolyEquationsCase1) {
    ::Tasks::EquationsTask task("x ^ 4 - 6 * x + 3 , -1 , 100", ::Tasks::TaskTypes::EqPoly); // " x ^ 4 - 1 , 1 , 100" функция, начальное приближение, итерации
    std::string actual = task.Solve();

    std::string expected = "x = 0.51140"; // находит ближайший к начальному приближению корень
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(EquationsTest, EmptyPolyEquationsCase) {
    ::Tasks::EquationsTask task("", ::Tasks::TaskTypes::EqPoly);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataPolyEquationsCase1) {
    ::Tasks::EquationsTask task("x-1 , 2 , 100",
                                ::Tasks::TaskTypes::EqPoly);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataPolyEquationsCaseWrongAlphas) {
    ::Tasks::EquationsTask task("x + a , 2 , 100",
                                ::Tasks::TaskTypes::EqPoly);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataPolyEquationsCaseWrongX_0) {
    ::Tasks::EquationsTask task("x - 1 , a , 100",
                                ::Tasks::TaskTypes::EqPoly);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataPolyEquationsCaseWrongDoubleX_0) {
    ::Tasks::EquationsTask task("x - 1 , 1.2.fg , 100",
                                ::Tasks::TaskTypes::EqPoly);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataPolyEquationsCaseDoubleIters) {
    ::Tasks::EquationsTask task("x - 1 , 1 , 100.45",
                                ::Tasks::TaskTypes::EqPoly);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataPolyEquationsCaseAlphasIters) {
    ::Tasks::EquationsTask task("x - 1 , 1 , 100s45a",
                                ::Tasks::TaskTypes::EqPoly);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataPolyEquationsCaseWrongArgumentsNum) {
    ::Tasks::EquationsTask task("x - 1 , 1 , 100 , ",
                                ::Tasks::TaskTypes::EqPoly);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}