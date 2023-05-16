#include <gtest/gtest.h>

#include <string>

#include "Exceptions.hpp"
#include "IntegrationsTask.hpp"
#include "TaskInfo.hpp"

// ------------------------- Линейные уравнения -------------------------------

TEST(EquationsTest, BasicLinearEquationsCase) {
    ::Tasks::EquationsTask task("4 3", ::Tasks::TaskTypes::EqLin);  // линейное уравнение имеет вид a * x = b

    std::string actual = task.Solve();

    std::string expected = "x = 0.75";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(EquationsTest, InvalidDataEquationsCase1) {
    ::Tasks::EquationsTask task("3v x = 3", ::Tasks::TaskTypes::EqLin);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataEquationsCase2) {
    ::Tasks::EquationsTask task("3 * x", ::Tasks::TaskTypes::EqLin);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataEquationsCase3) {
    ::Tasks::EquationsTask task("3* x", ::Tasks::TaskTypes::EqLin);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataEquationsCase4) {
    ::Tasks::EquationsTask task("3 * x 2", ::Tasks::TaskTypes::EqLin);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, DivideByZeroEquationsCase) {
    ::Tasks::EquationsTask task("0 5", ::Tasks::TaskTypes::EqLin);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// ------------------------- Квадратные уравнения -------------------------------

TEST(EquationsTest, BasicSquareEquationsCase) {
    ::Tasks::EquationsTask task("4 6 0", ::Tasks::TaskTypes::EqSq);
    std::string actual = task.Solve();

    std::string expected = "x_1 = 0.00000, x_2 = 1.50000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(EquationsTest, BasicSquareOneRootEquationsCase) {
    ::Tasks::EquationsTask task("4 -4 1", ::Tasks::TaskTypes::EqSq);
    std::string actual = task.Solve();

    std::string expected = "x = 0.5";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(EquationsTest, InvalidDataSqEquationsCase1) {
    ::Tasks::EquationsTask task("d4 * sdx ^ 2 - 6 * dx = 0", ::Tasks::TaskTypes::EqSq);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataSqEquationsCase2) {
    ::Tasks::EquationsTask task("4 *x - 6 * x = 0", ::Tasks::TaskTypes::EqSq);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataSqEquationsCase3) {
    ::Tasks::EquationsTask task("4 * x ^ 2 - 6 * x ", ::Tasks::TaskTypes::EqSq);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataSqEquationsCase4) {
    ::Tasks::EquationsTask task("4 * x ^ 2 - 6 * x - 4 = 4 * x",
                                ::Tasks::TaskTypes::EqSq);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, DivideByZeroSqEquationsCase) {
    ::Tasks::EquationsTask task("0 * x ^ 2 + 0 * x = 0", ::Tasks::TaskTypes::EqSq);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, DLessThanZeroSqEquationsCase) {
    ::Tasks::EquationsTask task("2 1 5",
                                ::Tasks::TaskTypes::EqSq);  // Дискриминант меньше нуля

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// ------------------------- Полиномиальные уравнения -------------------------------

TEST(EquationsTest, BasicPolyEquationsCase) {
    ::Tasks::EquationsTask task("x ^ 4 - 3 x ^ 3 - 13 * x ^ 2 + 27 * x + 90", ::Tasks::TaskTypes::EqPoly);
    std::string actual = task.Solve();

    std::string expected = "x = -1.31607";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(EquationsTest, EmptyPolyEquationsCase) {
    ::Tasks::EquationsTask task("", ::Tasks::TaskTypes::EqPoly);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataPolyEquationsCase1) {
    ::Tasks::EquationsTask task("d4 * sdx ^ 2 - 6 * dx = 0",
                                ::Tasks::TaskTypes::EqPoly);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataPolyEquationsCase2) {
    ::Tasks::EquationsTask task("4 * x ^ 6 - 6 * x =0",
                                ::Tasks::TaskTypes::EqPoly);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, InvalidDataPolyEquationsCase3) {
    ::Tasks::EquationsTask task("4 * x ^ 2 - 6 * x",
                                ::Tasks::TaskTypes::EqPoly);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}