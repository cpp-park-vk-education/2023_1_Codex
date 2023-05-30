#include <gtest/gtest.h>

#include <string>

#include "ArithmeticTask.hpp"
#include "Exceptions.hpp"
#include "IntegrationTask.hpp"
#include "TaskInfo.hpp"

// ------------------------- Ньютон-Котес -------------------------------

TEST(IntegrationTest, BasicIntegralNewtonCase) {
    ::Tasks::IntegrationTask task("x ^ 2 , 0 1 , 1000",
                                  ::Tasks::TaskTypes::IntegNewton);  // "Подынтегральное выражение , границы
                                                                     // интегрирования , число узлов"
    std::string actual = task.Solve();

    std::string expected = "0.33333";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(IntegrationTest, InvalidDataIntegralNewtonCaseFuncWithNums) {
    ::Tasks::IntegrationTask task("x 3 ^ 2 * f, 0 1 , 33",
                                  ::Tasks::TaskTypes::IntegNewton);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, InvalidDataIntegralNewtonCaseFuncWithoutSpace) {
    ::Tasks::IntegrationTask task("x^2 , 0 1",
                                  ::Tasks::TaskTypes::IntegNewton);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, InvalidNodesIntegralNewtonCaseNegativeNodes) {
    ::Tasks::IntegrationTask task("x ^ 2 , 0 1 , -3",
                                  ::Tasks::TaskTypes::IntegNewton);  // Отрицательное количество узлов

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, InvalidNodesIntegralNewtonCaseNodesNotNums) {
    ::Tasks::IntegrationTask task("x ^ 2 , 0 1sa , 3",
                                  ::Tasks::TaskTypes::IntegNewton);  // Неверный диапазон узлов

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, InvalidNodesIntegralNewtonCaseNodesCountNotNum) {
    ::Tasks::IntegrationTask task("x ^ 2 , 0 1 , 3sd",
                                  ::Tasks::TaskTypes::IntegNewton);  // Количество узлов - не число

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, InvalidNodesIntegralNewtonCaseNodesWrongAmount) {
    ::Tasks::IntegrationTask task("x ^ 2 , 0 1 2 , 1000",
                                  ::Tasks::TaskTypes::IntegNewton);  // Неверное количество узлов

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, InvalidNodesIntegralNewtonCaseNodesCountWrongAmount) {
    ::Tasks::IntegrationTask task("x ^ 2 , 0 1 , 1000 2345 4",
                                  ::Tasks::TaskTypes::IntegNewton);  // Неверное количество узлов

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, InvalidNodesIntegralNewtonCaseEmptyString) {
    ::Tasks::IntegrationTask task(" , , ",
                                  ::Tasks::TaskTypes::IntegNewton);  // Пустые аргументы

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, InvalidNodesIntegralNewtonCaseWrongArgumentsAmount) {
    ::Tasks::IntegrationTask task("x ^ 2 , 0 , 2 , 4",
                                  ::Tasks::TaskTypes::IntegNewton);  // Неверное количество аргументов

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, InvalidNodesIntegralNewtonCaseEmptyStr) {
    ::Tasks::IntegrationTask task("",
                                  ::Tasks::TaskTypes::IntegNewton);  // Неверное количество аргументов

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, InvalidNodesIntegralNewtonCaseWrongLessNode) {
    ::Tasks::IntegrationTask task("x ^ 2 , 0 -1 , 1000",
                                  ::Tasks::TaskTypes::IntegNewton);  // Неверный диапазон узлов

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// ------------------------- Симпсон -------------------------------

// В других методах интегрирования используется тот же парсер данных, поэтому не имеет смысла повторно
// тестировать корректность введенных данных. Гораздно важнее совпадение с правильным ответом

TEST(IntegrationTest, BasicIntegralSimpsonCase) {
    ::Tasks::IntegrationTask task("x ^ 2 , 0 1 , 1000",
                                  ::Tasks::TaskTypes::IntegSimpson);  // "Подынтегральное выражение , границы
                                                                      // интегрирования , число узлов"
    std::string actual = task.Solve();

    std::string expected = "0.33333";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(IntegrationTest, NegativeNodesIntegralSimpsonCase) {
    ::Tasks::IntegrationTask task("1 / 0 , 0 1 , 3", ::Tasks::TaskTypes::IntegSimpson);  // деление на ноль

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// ------------------------- Формула трапеций -------------------------------

TEST(IntegrationTest, BasicIntegralTrapezoidCase) {
    ::Tasks::IntegrationTask task("x ^ 2 , 0 1 , 1000",
                                  ::Tasks::TaskTypes::IntegTrapez);  // "Подынтегральное выражение , границы
                                                                     // интегрирования , число узлов"
    std::string actual = task.Solve();

    std::string expected = "0.33333";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}