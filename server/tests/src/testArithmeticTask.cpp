#include <gtest/gtest.h>

#include <string>

#include "ArithmeticTask.hpp"
#include "Exceptions.hpp"
#include "TaskInfo.hpp"

TEST(ArithmeticTest, SimpleNumberCase) {
    ::Tasks::ArithmeticTask task("12", ::Tasks::TaskTypes::Arithmetic);
    std::string actual = task.Solve();

    std::string expected = "12.00000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(ArithmeticTest, BasicCase) {
    ::Tasks::ArithmeticTask task("12 + ( 2 - 5 * 10 ) / 2", ::Tasks::TaskTypes::Arithmetic);
    std::string actual = task.Solve();

    std::string expected = "-12.00000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(ArithmeticTest, BasicDoubleCase) {
    ::Tasks::ArithmeticTask task("15 / 6 + 0.126", ::Tasks::TaskTypes::Arithmetic);
    std::string actual = task.Solve();

    std::string expected = "2.62600";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(ArithmeticTest, DivisionByZeroCase) {
    ::Tasks::ArithmeticTask task("23 / 0", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(ArithmeticTest, SqrtNotDefined) {
    ::Tasks::ArithmeticTask task("sqrt ( - 20 )", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(ArithmeticTest, DegreeNotDefined) {
    ::Tasks::ArithmeticTask task(" ( - 20 ) ^ ( 3 / 4 ) ", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

//Логарифмы и факториалы 

TEST(ArithmeticTest, LogarifmNotDefined) {
    ::Tasks::ArithmeticTask task("ln ( -10 )", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(ArithmeticTest, FactorialNotDefined) {
    ::Tasks::ArithmeticTask task("2.5 !", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(ArithmeticTest, FactorialIsTooBig) {
    ::Tasks::ArithmeticTask task("100 !", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// ---------InvalidData------------------------------------------------------

TEST(ArithmeticTest, InvalidDataCase1) {
    ::Tasks::ArithmeticTask task("abc + 23s", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(ArithmeticTest, InvalidDataCase2) {
    ::Tasks::ArithmeticTask task("12 / 23s", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(ArithmeticTest, InvalidDataCase3) {
    ::Tasks::ArithmeticTask task("a12 / 23", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(ArithmeticTest, InvalidDataCase4) {
    ::Tasks::ArithmeticTask task("1_2 / 23", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(ArithmeticTest, InvalidDataCase5) {
    ::Tasks::ArithmeticTask task("1,2 / 23", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(ArithmeticTest, InvalidFormatCase) {
    ::Tasks::ArithmeticTask task("1*3+8-9", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}