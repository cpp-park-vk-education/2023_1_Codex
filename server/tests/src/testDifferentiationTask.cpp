#include <gtest/gtest.h>

#include <string>

#include "DifferentiationTask.hpp"
#include "Exceptions.hpp"
#include "TaskInfo.hpp"

// Символьное дифференцирование еще не реализовано
/*
TEST(DifferentiationTest, BasicCaseSymbolic) {
    ::Tasks::DifferentiationTask task(" 12 * x ^ 2 + sin ( x ) - 6 ) ", ::Tasks::TaskTypes::DiffSymb);
    std::string actual = task.Solve();

    std::string expected = "24 * x + cos ( x )";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}*/

TEST(DifferentiationTest, BasicCaseNumerical) {
    ::Tasks::DifferentiationTask task(" 12 * x ^ 2 + sin ( x ) - 6  ; 2", ::Tasks::TaskTypes::DiffNum);
    std::string actual = task.Solve();

    std::string expected = "47.58386";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(DifferentiationTest, NoPointProvided) {
    ::Tasks::DifferentiationTask task(" 12 * x ^ 2 + sin ( x ) - 6  ; ", ::Tasks::TaskTypes::DiffNum);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(DifferentiationTest, FunctionNotDefinedInPoint) {
    ::Tasks::DifferentiationTask task("  x ^ ( 1 / 2 ) ; -23 ", ::Tasks::TaskTypes::DiffNum);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// ---------InvalidData------------------------------------------------------
TEST(DifferentiationTest, InvalidDataCase11) {
    ::Tasks::DifferentiationTask task("abc + 23s ; 8", ::Tasks::TaskTypes::DiffNum);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(DifferentiationTest, InvalidDataCase12) {
    ::Tasks::DifferentiationTask task("a32c + 23 ; 8", ::Tasks::TaskTypes::DiffNum);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(DifferentiationTest, InvalidDataCase13) {
    ::Tasks::DifferentiationTask task("1 + 23 * x ; 8gh ", ::Tasks::TaskTypes::DiffNum);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(DifferentiationTest, InvalidDataCase14) {
    ::Tasks::DifferentiationTask task("1 + 23 * v ; 85 ", ::Tasks::TaskTypes::DiffNum);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

//Тесты для символьного дифференцирования, оно пока не реализованно
/*
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
    ::Tasks::ArithmeticTask task("5*x+8-x", ::Tasks::TaskTypes::DiffSymb);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}*/