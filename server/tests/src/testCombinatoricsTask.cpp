#include <gtest/gtest.h>

#include <string>

#include "IntegrationsTask.hpp"
#include "exceptions.hpp"
#include "taskInfo.hpp"

//--------------------------- Сочетания -------------------------------------------

TEST(CombinatoricsTest, BasicCombCase) {
    ::Tasks::CombinatoricsTask task("2 8",
                                    ::Tasks::TaskTypes::CombComb);  // C^k_n, в строке оказываются только k и
                                                                    // n -> для данного примера k = 2, n = 8
    std::string actual = task.Solve();

    std::string expected = "28";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(CombinatoricsTest, InvalidKValueCombCase) {
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
        "400 600", ::Tasks::TaskTypes::CombComb);  // при n/n-k > 14 число комбинаций становится
                                                   // трудновычислимым и требует больших затрат памяти и
                                                   // вычислительных ресурсов

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataCombCase1) {
    ::Tasks::CombinatoricsTask task("40sd 3", ::Tasks::TaskTypes::CombComb);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataCombCase2) {
    ::Tasks::CombinatoricsTask task("4 а", ::Tasks::TaskTypes::CombComb);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataCombCase3) {
    ::Tasks::CombinatoricsTask task("4 5 6", ::Tasks::TaskTypes::CombComb);

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
        ::Tasks::TaskTypes::CombRe);  // большие значения n (>14) являются трудновычислимыми:
                                      // 50! =
                                      // 30414093201713378043612608166064768844377641568960512000000000000

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataReCase1) {
    ::Tasks::CombinatoricsTask task("40sd", ::Tasks::TaskTypes::CombRe);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataReCase2) {
    ::Tasks::CombinatoricsTask task("4 5", ::Tasks::TaskTypes::CombRe);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

//--------------------------- Размещения -------------------------------------------

TEST(CombinatoricsTest, BasicPlaceCase) {
    ::Tasks::CombinatoricsTask task(
        "2 4" ::Tasks::TaskTypes::CombPlace);  // A^k_n, в данном кейсе пытаемся посчитать число размещений из
                                               // 4 по 2
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

TEST(CombinatoricsTest, DecimalValuesPlaceCase1) {
    ::Tasks::CombinatoricsTask task("5.71 6", ::Tasks::TaskTypes::CombPlace);  // целые числа

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, DecimalValuesPlaceCase2) {
    ::Tasks::CombinatoricsTask task("5 6.6", ::Tasks::TaskTypes::CombPlace);  // целые числа

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, LargeValuesPlaceCase) {
    ::Tasks::CombinatoricsTask task(
        "50 30",
        ::Tasks::TaskTypes::CombPlace);  //при n/n-k > 14 число комбинаций становится трудновычислимым и
                                         //требует больших затрат памяти и вычислительных ресурсов

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataPlaceCase1) {
    ::Tasks::CombinatoricsTask task("40sd 4", ::Tasks::TaskTypes::CombPlace);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataPlaceCase2) {
    ::Tasks::CombinatoricsTask task("4 4d", ::Tasks::TaskTypes::CombPlace);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataPlaceCase3) {
    ::Tasks::CombinatoricsTask task("4 6 8", ::Tasks::TaskTypes::CombPlace);

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

TEST(CombinatoricsTest, InvalidDataPartCase1) {
    ::Tasks::CombinatoricsTask task("40sd", ::Tasks::TaskTypes::CombPart);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(CombinatoricsTest, InvalidDataPartCase2) {
    ::Tasks::CombinatoricsTask task("4 5", ::Tasks::TaskTypes::CombPart);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}