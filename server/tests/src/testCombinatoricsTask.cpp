#include <gtest/gtest.h>

#include <string>

#include "CombinatoricsTask.hpp"
#include "Exceptions.hpp"
#include "IntegrationTask.hpp"
#include "TaskInfo.hpp"

//--------------------------- Сочетания -------------------------------------------

TEST(CombinatoricsTest, BasicCombCase) {
    ::Tasks::CombinatoricsTask task("2 8",
                                    ::Tasks::TaskTypes::CombComb);  // C^k_n, в строке оказываются только k и
                                                                    // n -> для данного примера k = 2, n = 8
    std::string actual = task.Solve();

    std::string expected = "28";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(CombinatoricsTest, InvalidValueCombCaseKLargerN) {
    ::Tasks::CombinatoricsTask task("8 2", ::Tasks::TaskTypes::CombComb);  // k не может быть больше n

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, NegativeValuesCombCase) {
    ::Tasks::CombinatoricsTask task("-5 -4", ::Tasks::TaskTypes::CombComb);  // k и n - неотрицательные числа

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, DecimalValuesCombCase) {
    ::Tasks::CombinatoricsTask task("4 5.71", ::Tasks::TaskTypes::CombComb);  // k и n - целые числа

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, LargeValuesCombCase) {
    ::Tasks::CombinatoricsTask task(
        "400 600", ::Tasks::TaskTypes::CombComb);  // при слишком больших значениях вычисление комбинаций
                                                   // становится ресурсозатратным и времязатратным

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataCombCasePartNotNums) {
    ::Tasks::CombinatoricsTask task("4sd 12", ::Tasks::TaskTypes::CombComb);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataCombCaseNotNums) {
    ::Tasks::CombinatoricsTask task("4 а", ::Tasks::TaskTypes::CombComb);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataCombCaseWrongAmount) {
    ::Tasks::CombinatoricsTask task("4 5 6", ::Tasks::TaskTypes::CombComb);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataCombCaseEmptyStr) {
    ::Tasks::CombinatoricsTask task("", ::Tasks::TaskTypes::CombComb);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

//--------------------------- Перестановки -------------------------------------------

TEST(CombinatoricsTest, BasicReshuffleCase) {
    ::Tasks::CombinatoricsTask task(
        "4", ::Tasks::TaskTypes::CombRe);  // P^n, в строке задается только n -> в данном кейсе пытаемся
                                           // посчитать число перестановок из 4 элементов
    std::string actual = task.Solve();

    std::string expected = "24";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(CombinatoricsTest, NegativeValuesReCase) {
    ::Tasks::CombinatoricsTask task("-5", ::Tasks::TaskTypes::CombRe);  // n - неотрицательное число

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, DecimalValuesReCase) {
    ::Tasks::CombinatoricsTask task("5.71", ::Tasks::TaskTypes::CombRe);  // n - целое число

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, LargeValuesReCase) {
    ::Tasks::CombinatoricsTask task(
        "50",
        ::Tasks::TaskTypes::CombRe);  // большие значения n являются трудновычислимыми

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataReCaseNotNums) {
    ::Tasks::CombinatoricsTask task("4sd", ::Tasks::TaskTypes::CombRe);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataReCaseWrongAmount) {
    ::Tasks::CombinatoricsTask task("4 5", ::Tasks::TaskTypes::CombRe);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataReCaseEmptyStr) {
    ::Tasks::CombinatoricsTask task("", ::Tasks::TaskTypes::CombRe);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

//--------------------------- Размещения -------------------------------------------

TEST(CombinatoricsTest, BasicPlaceCase) {
    ::Tasks::CombinatoricsTask task("2 4",
                                    ::Tasks::TaskTypes::CombPlace);  // A^k_n, в данном кейсе пытаемся
                                                                     // посчитать число размещений из 4 по 2
    std::string actual = task.Solve();

    std::string expected = "12";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(CombinatoricsTest, InvalidKValuePlaceCase) {
    ::Tasks::CombinatoricsTask task("4 2", ::Tasks::TaskTypes::CombPlace);  // k не может быть больше n

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, NegativeValuesPlaceCase) {
    ::Tasks::CombinatoricsTask task("-5 -3", ::Tasks::TaskTypes::CombPlace);  // неотрицательные числа

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, DecimalValuesPlaceCase) {
    ::Tasks::CombinatoricsTask task("5.71 6", ::Tasks::TaskTypes::CombPlace);  // целые числа

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, LargeValuesPlaceCase) {
    ::Tasks::CombinatoricsTask task("70 60",
                                    ::Tasks::TaskTypes::CombPlace);  // большие значения

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataPlaceCaseNotNums) {
    ::Tasks::CombinatoricsTask task("40sd 4", ::Tasks::TaskTypes::CombPlace);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataPlaceCaseWrongAmount) {
    ::Tasks::CombinatoricsTask task("4 6 8", ::Tasks::TaskTypes::CombPlace);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataPlaceCaseEmptyString) {
    ::Tasks::CombinatoricsTask task("", ::Tasks::TaskTypes::CombPlace);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

//--------------------------- Разбиения -------------------------------------------

TEST(CombinatoricsTest, BasicPartCase) {
    ::Tasks::CombinatoricsTask task(
        "4", ::Tasks::TaskTypes::CombPart);  // P^n, в строке задается только n -> в данном кейсе пытаемся
                                             // посчитать число разбиений числа 4
    std::string actual = task.Solve();

    std::string expected = "4";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(CombinatoricsTest, NegativeValuesPartCase) {
    ::Tasks::CombinatoricsTask task("-5", ::Tasks::TaskTypes::CombPart);  // n - неотрицательное число

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, DecimalValuesPartCase) {
    ::Tasks::CombinatoricsTask task("5.71", ::Tasks::TaskTypes::CombPart);  // n - целое число

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, LargeValuesPartCase) {
    ::Tasks::CombinatoricsTask task("100",
                                    ::Tasks::TaskTypes::CombPart);  // большие значения n

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataPartCasePartlyNotNums) {
    ::Tasks::CombinatoricsTask task("40sd", ::Tasks::TaskTypes::CombPart);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataPartCaseNotNums) {
    ::Tasks::CombinatoricsTask task("a", ::Tasks::TaskTypes::CombPart);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataPartCaseWrongAmount) {
    ::Tasks::CombinatoricsTask task("4 5", ::Tasks::TaskTypes::CombPart);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataPartCaseEmptyString) {
    ::Tasks::CombinatoricsTask task("", ::Tasks::TaskTypes::CombPart);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}