#include <gtest/gtest.h>

#include <string>

#include "exceptions.hpp"
#include "ArithmeticTask.hpp"
#include "taskInfo.hpp"

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

TEST(ArithmeticTest, InvalidDataCase) {
    ::Tasks::ArithmeticTask task("abc + 23s", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(ArithmeticTest, InvalidFormatCase) {
    ::Tasks::ArithmeticTask task("1*3+8-9", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
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