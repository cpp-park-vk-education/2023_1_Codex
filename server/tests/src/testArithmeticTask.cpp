#include <gtest/gtest.h>

#include <string>

#include "ArithmeticTask.hpp"
#include "Exceptions.hpp"
#include "TaskInfo.hpp"

TEST(ArithmeticTest, SimpleNumberCase) {
    ::Tasks::ArithmeticTask task("12", ::Tasks::TaskTypes::Arithmetic);
    std::string actual = task.Solve();

    std::string expected = "12";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(ArithmeticTest, BasicCase) {
    ::Tasks::ArithmeticTask task("12 + ( 2 - 5 * 10 ) / 2", ::Tasks::TaskTypes::Arithmetic);
    std::string actual = task.Solve();

    std::string expected = "36";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(ArithmeticTest, BasicDoubleCase) {
    ::Tasks::ArithmeticTask task("15 / 6 + 0.126", ::Tasks::TaskTypes::Arithmetic);
    std::string actual = task.Solve();

    std::string expected = "2.626";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(ArithmeticTest, DivisionByZeroCase) {
    ::Tasks::ArithmeticTask task("23 / 0", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::DivisionByZero);
}

TEST(ArithmeticTest, SqrtNotDefined) {
    ::Tasks::ArithmeticTask task("sqrt ( - 20 )", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::SqrtNotDefined);
}

TEST(ArithmeticTest, LogarifmNotDefined) {
    ::Tasks::ArithmeticTask task("ln ( - 10 )", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::LogarifmNotDefined);
}

TEST(ArithmeticTest, LogarifmNotDefined) {
    ::Tasks::ArithmeticTask task("2.5 !", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::FactorialOfNotInteger);
}

TEST(ArithmeticTest, LogarifmNotDefined) {
    ::Tasks::ArithmeticTask task("100 !", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::TooBigFactorial);
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