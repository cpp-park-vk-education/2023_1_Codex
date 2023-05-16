#include <gtest/gtest.h>

#include <string>

#include "IntegrationsTask.hpp"
#include "exceptions.hpp"
#include "taskInfo.hpp"

// ------------------------- Ньютон-Котес -------------------------------

TEST(IntegrationTest, BasicIntegralNewtonCase) {
    ::Tasks::IntegrationsTask task("x ^ 2 , 0 1 , 1000",
                                   ::Tasks::TaskTypes::IntegNewton);  // "Подынтегральное выражение , границы
                                                                      // интегрирования , число узлов"
    std::string actual = task.Solve();

    std::string expected = "0.33333";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(IntegrationTest, InvalidDataIntegralNewtonCase1) {
    ::Tasks::IntegrationsTask task("x 3 ^ 2 f, 0 1s , 33",
                                   ::Tasks::TaskTypes::IntegNewton);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, InvalidDataIntegralNewtonCase2) {
::Tasks::IntegrationsTask task("x^2 , 0 1",
                               ::Tasks::TaskTypes::IntegNewton);  // Неверное выражение

EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, InvalidNodesIntegralNewtonCase) {
    ::Tasks::IntegrationsTask task("x ^ 2 , 0 1 , -3",
                                   ::Tasks::TaskTypes::IntegNewton);  // Неверное количество узлов

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// ------------------------- Симпсон -------------------------------

TEST(IntegrationTest, BasicIntegralSimpsonCase) {
    ::Tasks::IntegrationsTask task("x ^ 3 + 2 * x ^ 2 + 1 , 0 2 , 4",
                                   ::Tasks::TaskTypes::IntegSimpson);  // "Подинтегральное выражение , границы
                                                                       // интегрирования , число узлов"
    std::string actual = task.Solve();

    std::string expected = "11.33333";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(IntegrationTest, InvalidDataIntegralSimpsonCase) {
    ::Tasks::IntegrationsTask task("x^3 + 2x^2 + 1b 0 1s , 33",
                                   ::Tasks::TaskTypes::IntegSimpson);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, InvalidNodesIntegralSimpsonCase) {
    ::Tasks::IntegrationsTask task(
        "x^3 + 2x^2 + 1 , 0 1 , 5",
        ::Tasks::TaskTypes::IntegSimpson);  // Неверное количество узлов (должно быть четное)

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, NegativeNodesIntegralSimpsonCase) {
    ::Tasks::IntegrationsTask task("x^3 + 2x^2 + 1 , 0 1 , -4",
                                   ::Tasks::TaskTypes::IntegSimpson);  // Неверное количество узлов

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, InvalidNodesIntegralNewtonCase) {
    ::Tasks::IntegrationsTask task("1 / x , 0 1 , -3", ::Tasks::TaskTypes::IntegSimpson);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// ------------------------- Формула трапеций -------------------------------

TEST(IntegrationTest, BasicIntegralTrapezoidCase) {
    ::Tasks::IntegrationsTask task("x ^ 3 + 2 * x ^ 2 + 1 , 0 2 , 4",
                                   ::Tasks::TaskTypes::IntegTrapez);  // "Подинтегральное выражение , границы
                                                                      // интегрирования , число узлов"
    std::string actual = task.Solve();

    std::string expected = "11.75";  // Результат отличается из-за другого метода интегрирования
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(IntegrationTest, InvalidDataIntegralTrapezoidCase) {
    ::Tasks::IntegrationsTask task("x ^ 3 + 2 * x ^ 2 + 1b 0 1s , 33",
                                   ::Tasks::TaskTypes::IntegTrapez);  // Неверное выражение

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, NegativeNodesIntegralTrapezoidCase) {
    ::Tasks::IntegrationsTask task("x ^ 3 + 2 * x ^ 2 + 1 , 0 1 , -4",
                                   ::Tasks::TaskTypes::IntegTrapez);  // Неверное количество узлов

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(IntegrationTest, InvalidNodesIntegralNewtonCase) {
    ::Tasks::IntegrationsTask task("1 / x , 0 1 , -3", ::Tasks::TaskTypes::IntegTrapez);
    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}
