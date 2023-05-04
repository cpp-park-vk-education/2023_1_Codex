#include <gtest/gtest.h>

#include <string>

#include "exceptions.hpp"
#include "DifferentiationTask.hpp"
#include "taskInfo.hpp"

TEST(DifferentiationTest, BasicCaseSymbolic) {
    ::Tasks::DifferentiationTask task(" 12 * x ^ 2 + sin ( x ) - 6 ) ", ::Tasks::TaskTypes::DiffSymb);
    std::string actual = task.Solve();

    std::string expected = "24 * x + cos ( x )";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(DifferentiationTest, BasicCaseNumerical) {
    ::Tasks::DifferentiationTask task(" 12 * x ^ 2 + sin ( x ) - 6 ) ; 2", ::Tasks::TaskTypes::DiffNum);
    std::string actual = task.Solve();

    std::string expected = "47.58385";
    EXPECT_STREQ(expected.c_str(), actual.c_str());

}


TEST(DifferentiationTest, NoPointProvided) {
    ::Tasks::DifferentiationTask task(" 12 * x ^ 2 + sin ( x ) - 6 ) ; ", ::Tasks::TaskTypes::DiffNum);

    EXPECT_THROW(task.Solve(), ::Tasks::NoPointProvided);
}

TEST(DifferentiationTest, FunctionNotDefinedInPoint) {
    ::Tasks::DifferentiationTask task(" x ^ ( 1 / 2 ) ; -23 ", ::Tasks::TaskTypes::DiffNum);

    EXPECT_THROW(task.Solve(), ::Tasks::FunctionNotDefinedInPoint);
}

// ---------InvalidData------------------------------------------------------
TEST(DifferentiationTest, InvalidDataCase1) {
    ::Tasks::DifferentiationTask task("abc + 23s", ::Tasks::TaskTypes::DiffSymb);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(DifferentiationTest, InvalidDataCase2) {
    ::Tasks::DifferentiationTask task("a1 + 23", ::Tasks::TaskTypes::DiffSymb);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(DifferentiationTest, InvalidDataCase2) {
    ::Tasks::DifferentiationTask task("1 / 23s", ::Tasks::TaskTypes::DiffSymb);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(DifferentiationTest, InvalidDataCase2) {
    ::Tasks::DifferentiationTask task("1 * 23 / s", ::Tasks::TaskTypes::DiffSymb);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(ArithmeticTest, InvalidFormatCase) {
    ::Tasks::ArithmeticTask task("5*x+8-x", ::Tasks::TaskTypes::Arithmetic);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}