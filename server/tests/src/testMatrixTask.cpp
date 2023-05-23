#include <gtest/gtest.h>

#include <string>

#include "Exceptions.hpp"
#include "MatrixTask.hpp"
#include "TaskInfo.hpp"

// ---------Determinant--------------------------------------------------------
TEST(MatrixTest, BasicCaseDeterminant) {
    ::Tasks::MatrixTask task("2 3 4 / 4 5 6 / 0 9 2  ", ::Tasks::TaskTypes::MatrixDet);
    std::string actual = task.Solve();

    std::string expected = "32.00000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

// ---------Transpose--------------------------------------------------------
TEST(MatrixTest, BasicCaseTranspose) {
    ::Tasks::MatrixTask task("2 3 4 / 4 5 6 / 0 9 2  ", ::Tasks::TaskTypes::MatrixT);
    std::string actual = task.Solve();

    std::string expected = "2.00000 4.00000 0.00000 / 3.00000 5.00000 9.00000 / 4.00000 6.00000 2.00000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

// ---------EigenValuesAndVectors--------------------------------------------------------
TEST(MatrixTest, BasicCaseEigenValuesAndVectors) {
    ::Tasks::MatrixTask task("1 0 0 / 0 2 0 / 0 0 3", ::Tasks::TaskTypes::MatrixEigen);
    std::string actual = task.Solve();

    std::string expected =
        "1.00000 : [ 1.00000,  0.00000,  0.00000 ] 2.00000 : [ 0.00000,  1.00000,  0.00000 ] 3.00000 : [ 0.00000,  0.00000,  1.00000 ]";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(MatrixTest, NotSquareMarixEigenValuesAndVectors) {
    ::Tasks::MatrixTask task("1 2 3 / 2 5 8 ", ::Tasks::TaskTypes::MatrixEigen);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// ---------Rank--------------------------------------------------------
TEST(MatrixTest, BasicCaseRank) {
    ::Tasks::MatrixTask task("1 2 2 4 / 23 14 25 -9 / 7 124 3 2", ::Tasks::TaskTypes::MatrixRank);
    std::string actual = task.Solve();

    std::string expected = "3.00000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

// ---------Norma--------------------------------------------------------
TEST(MatrixTest, BasicCaseNorma) {
    ::Tasks::MatrixTask task("1 2 3 / 2 5 8 / 3 1 2", ::Tasks::TaskTypes::MatrixNorm);
    std::string actual = task.Solve();

    std::string expected = "11.00000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

// ---------InvalidData------------------------------------------------------
TEST(MatrixTest, InvalidData1) {
    ::Tasks::MatrixTask task("1 2 3 / 2 5 / 2 2 5 ", ::Tasks::TaskTypes::MatrixDet);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(MatrixTest, InvalidData2) {
    ::Tasks::MatrixTask task("avd df cd / 2 4 5 / 2 2 5 ", ::Tasks::TaskTypes::MatrixDet);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(MatrixTest, InvalidData3) {
    ::Tasks::MatrixTask task("2 1 1a / 2 4 5 / 2 2 5 ", ::Tasks::TaskTypes::MatrixDet);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(MatrixTest, InvalidData4) {
    ::Tasks::MatrixTask task("2 1 a1 / b2 4 5 / 2 2 5 ", ::Tasks::TaskTypes::MatrixDet);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}
