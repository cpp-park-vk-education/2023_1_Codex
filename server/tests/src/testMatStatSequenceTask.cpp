#include <gtest/gtest.h>

#include <string>

#include "Exceptions.hpp"
#include "MatStatSequenceTask.hpp"
#include "TaskInfo.hpp"

TEST(MatStatSequenceTaskTest, BasicIMCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8 / 1", ::Tasks::TaskTypes::MatStatSeqInitMoment);
    std::string actual = task.Solve();

    std::string expected = "4.50000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(MatStatSequenceTaskTest, InvalidDegreeIMCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8 / 0", ::Tasks::TaskTypes::MatStatSeqInitMoment);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(MatStatSequenceTaskTest, InvalidDataIMCase) {
    ::Tasks::MatStatSequenceTask task("a 45 / 2", ::Tasks::TaskTypes::MatStatSeqInitMoment);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// --------------------------------------------------------------------------------

TEST(MatStatSequenceTaskTest, BasicCMCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8 / 2", ::Tasks::TaskTypes::MatStatSeqCentralMoment);
    std::string actual = task.Solve();

    std::string expected = "5.25000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(MatStatSequenceTaskTest, InvalidDegreeCMCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8 / 0.5", ::Tasks::TaskTypes::MatStatSeqCentralMoment);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(MatStatSequenceTaskTest, InvalidDataCMCase) {
    ::Tasks::MatStatSequenceTask task("1qa 2 / 3", ::Tasks::TaskTypes::MatStatSeqCentralMoment);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// --------------------------------------------------------------------------------

TEST(MatStatSequenceTaskTest, BasicAsymmetryCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 9", ::Tasks::TaskTypes::MatStatSeqAsymmetry);
    std::string actual = task.Solve();

    std::string expected = "3.69141";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(MatStatSequenceTaskTest, InvalidAsymmetryCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8 f", ::Tasks::TaskTypes::MatStatSeqAsymmetry);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// --------------------------------------------------------------------------------

TEST(MatStatSequenceTaskTest, BasicExcessCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8", ::Tasks::TaskTypes::MatStatSeqExcess);
    std::string actual = task.Solve();

    std::string expected = "-1.23810";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(MatStatSequenceTaskTest, InvalidExcessCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 f 8", ::Tasks::TaskTypes::MatStatSeqExcess);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// --------------------------------------------------------------------------------

TEST(MatStatSequenceTaskTest, BasicQuantileCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8 / 0.5", ::Tasks::TaskTypes::MatStatSeqQuantile);
    std::string actual = task.Solve();

    std::string expected = "4.50000";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(MatStatSequenceTaskTest, InvalidDegreeQuantileCase) {
    ::Tasks::MatStatSequenceTask task("1 2 3 4 5 6 7 8 / 1.1", ::Tasks::TaskTypes::MatStatSeqQuantile);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(MatStatSequenceTaskTest, InvalidDataQuantileCase) {
    ::Tasks::MatStatSequenceTask task("1 2 e3 4 5 6 7 8 / 0.5", ::Tasks::TaskTypes::MatStatSeqQuantile);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}
