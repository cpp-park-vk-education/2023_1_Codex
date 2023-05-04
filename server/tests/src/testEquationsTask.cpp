#include <gtest/gtest.h>

#include <string>

#include "IntegrationsTask.hpp"
#include "exceptions.hpp"
#include "taskInfo.hpp"

// ------------------------- Линейные уравнения -------------------------------

TEST(EquationsTest, BasicLinearEquationsCase) {
    ::Tasks::EquationsTask task("4 * x = 3",
                                ::Tasks::TaskTypes::EqLin);  // линейное уравнение имеет вид a * x = b
    std::string actual = task.Solve();

    std::string expected = "x = 0.75";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(EquationsTest, InvalidDataEquationsCase) {
    ::Tasks::EquationsTask task("3v x = 3", ::Tasks::TaskTypes::EqLin);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, DivideByZeroEquationsCase) {
    ::Tasks::EquationsTask task("0 * x = 5", ::Tasks::TaskTypes::EqLin);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// ------------------------- Квадратные уравнения -------------------------------

TEST(EquationsTest, BasicSquareEquationsCase) {
    ::Tasks::EquationsTask task("4 * x ^ 2 - 6 * x = 0", ::Tasks::TaskTypes::EqSq);
    std::string actual = task.Solve();

    std::string expected = "x_1 = 0, x_2 = 1.5";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(EquationsTest, BasicSquareOneRootEquationsCase) {
    ::Tasks::EquationsTask task("4 * x ^ 2 - 4 * x + 1 = 0", ::Tasks::TaskTypes::EqSq);
    std::string actual = task.Solve();

    std::string expected = "x = 0.5";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(EquationsTest, InvalidDataSqEquationsCase) {
    ::Tasks::EquationsTask task("d4 * sdx ^ 2 - 6 * dx = 0", ::Tasks::TaskTypes::EqSq);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, DivideByZeroSqEquationsCase) {
    ::Tasks::EquationsTask task("0 * x ^ 2 + 0 * x = 0", ::Tasks::TaskTypes::EqSq);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(EquationsTest, DLessThanZeroSqEquationsCase) {
    ::Tasks::EquationsTask task("2 * x ^ 2 + x  + 5 = 0",
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

TEST(EquationsTest, InvalidDataPolyEquationsCase) {
    ::Tasks::EquationsTask task("d4 * sdx ^ 2 - 6 * dx = 0",
                                ::Tasks::TaskTypes::EqPoly);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}