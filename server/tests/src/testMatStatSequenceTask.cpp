#include <gtest/gtest.h>

#include <string>

#include "exceptions.hpp"
#include "matStatSequenceTask.hpp"
#include "taskInfo.hpp"

TEST(MatStatSequenceTest, BasicInitialMomentCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8 / 1", ::Tasks::TaskTypes::MatStatInitMoment);
    std::string actual = task.Solve();

    std::string expected = "4.5";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(MatStatSequenceTest, InvalidDegreeIMCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8 / 0", ::Tasks::TaskTypes::MatStatInitMoment);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(MatStatSequenceTest, InvalidDataIMCase) {
    ::Tasks::MatStatSequenceTask task("a 45 / 2", ::Tasks::TaskTypes::MatStatInitMoment);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// --------------------------------------------------------------------------------

TEST(MatStatSequenceTest, BasicCMCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8 / 2", ::Tasks::TaskTypes::MatStatCentralMoment);
    std::string actual = task.Solve();

    std::string expected = "42";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(MatStatSequenceTest, InvalidDegreeCMCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8 / 0.5", ::Tasks::TaskTypes::MatStatCentralMoment);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(MatStatSequenceTest, InvalidDataCMCase) {
    ::Tasks::MatStatSequenceTask task("1qa 2 / 3", ::Tasks::TaskTypes::MatStatCentralMoment);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// --------------------------------------------------------------------------------

TEST(MatStatSequenceTest, BasicAsymmetryCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8", ::Tasks::TaskTypes::MatStatAsymmetry);
    std::string actual = task.Solve();

    std::string expected = "19.13362";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(MatStatSequenceTest, InvalidAsymmetryCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8 f", ::Tasks::TaskTypes::MatStatAsymmetry);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// --------------------------------------------------------------------------------

TEST(MatStatSequenceTest, BasicExcessCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8", ::Tasks::TaskTypes::MatStatExcess);
    std::string actual = task.Solve();

    std::string expected = "56.94685";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(MatStatSequenceTest, InvalidExcessCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 f 8", ::Tasks::TaskTypes::MatStatExcess);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// --------------------------------------------------------------------------------

TEST(MatStatSequenceTest, BasicQuantileCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8 / 0.5", ::Tasks::TaskTypes::MatStatQuantile);
    std::string actual = task.Solve();

    std::string expected = "4.5";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(MatStatSequenceTest, InvalidDegreeQuantileCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8 / 1.1", ::Tasks::TaskTypes::MatStatQuantile);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(MatStatSequenceTest, InvalidDataQuantileCase) {
    ::Tasks::MatStatSequenceTask task("1 2 e3 4 5 6 7 8 / 0.5", ::Tasks::TaskTypes::MatStatQuantile);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}
