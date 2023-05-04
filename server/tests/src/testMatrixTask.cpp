#include <gtest/gtest.h>

#include <string>

#include "exceptions.hpp"
#include "MatrixTask.hpp"
#include "taskInfo.hpp"

// ---------Determinant--------------------------------------------------------
TEST(MatrixTest, BasicCaseDeterminant) {
    ::Tasks::MatrixTask task("2 3 4 / 4 5 6 / 0 9 2  ", ::Tasks::TaskTypes::MatrixDet);
    std::string actual = task.Solve();

    std::string expected = "32";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

// ---------Transpose--------------------------------------------------------
TEST(MatrixTest, BasicCaseTranspose) {
    ::Tasks::MatrixTask task("2 3 4 / 4 5 6 / 0 9 2  ", ::Tasks::TaskTypes::MatrixT);
    std::string actual = task.Solve();

    std::string expected = "2 4 0 / 3 5 9 / 4 6 2";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

// ---------EigenValuesAndVectors--------------------------------------------------------
TEST(MatrixTest, BasicCaseEigenValuesAndVectors) {
    ::Tasks::MatrixTask task("1 2 3 / 2 5 8 / 3 1 2", ::Tasks::TaskTypes::MatrixEigen);
    std::string actual = task.Solve();

    std::string expected = "0.29737 : [-2.71932, -0.54467, 1]; -2.83313 : [-1.19157, -2.59215, 1]; 11.86950 : [0.51804, 1.32539, 1] ";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(MatrixTest, NotSquareMarixEigenValuesAndVectors) {
    ::Tasks::MatrixTask task("1 2 3 / 2 5 8 ", ::Tasks::TaskTypes::MatrixEigen);
    
    EXPECT_THROW(task.Solve(), ::Tasks::NotSquareMarix);
}


// ---------Rank--------------------------------------------------------
TEST(MatrixTest, BasicCaseRank) {
    ::Tasks::MatrixTask task("1 2 2 4 / 23 14 25 -9 / 7 124 3 2", ::Tasks::TaskTypes::MatrixRank);
    std::string actual = task.Solve();

    std::string expected = "3";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}


// ---------Norma--------------------------------------------------------
TEST(MatrixTest, BasicCaseNorma) {
    ::Tasks::MatrixTask task("1 2 3 / 2 5 8 / 3 1 2", ::Tasks::TaskTypes::MatrixNorma);
    std::string actual = task.Solve();

    std::string expected = "10.73918023546";
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
