#include <gtest/gtest.h>

#include <string>

#include "Exceptions.hpp"
#include "LogicalExpressionTask.hpp"
#include "TaskInfo.hpp"

TEST(LogicalExpressionTest, BasicPDNFCase) {
    ::Tasks::LogicalExpressionTask task("!(a & !b)", ::Tasks::TaskTypes::LogicalPDNF);
    std::string actual = task.Solve();

    std::string expected = "!a & !b | !a & b | a & b";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(LogicalExpressionTest, BasicPDNFCase) {
    ::Tasks::LogicalExpressionTask task("!(a&!b)", ::Tasks::TaskTypes::LogicalPDNF);
    std::string actual = task.Solve();

    std::string expected = "!a & !b | !a & b | a & b";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(LogicalExpressionTest, SimplePDNFCase) {
    ::Tasks::LogicalExpressionTask task("!a & !b", ::Tasks::TaskTypes::LogicalPDNF);
    std::string actual = task.Solve();

    std::string expected = "!a & !b";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(LogicalExpressionTest, InvalidDataPDNFCase) {
    ::Tasks::LogicalExpressionTask task("!(a & !b", ::Tasks::TaskTypes::LogicalPDNF);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(LogicalExpressionTest, NoOperatorPDNFCase) {
    ::Tasks::LogicalExpressionTask task("!a !b", ::Tasks::TaskTypes::LogicalPDNF);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

// --------------------------------------------------------------------------------

TEST(LogicalExpressionTest, BasicPCNFCase) {
    ::Tasks::LogicalExpressionTask task("!(a & !b)", ::Tasks::TaskTypes::LogicalPCNF);
    std::string actual = task.Solve();

    std::string expected = "!a | b";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(LogicalExpressionTest, BasicPCNFCase) {
    ::Tasks::LogicalExpressionTask task("!(a&!b)", ::Tasks::TaskTypes::LogicalPCNF);
    std::string actual = task.Solve();

    std::string expected = "!a | b";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(LogicalExpressionTest, SimplePCNFCase) {
    ::Tasks::LogicalExpressionTask task("!a & !b", ::Tasks::TaskTypes::LogicalPCNF);
    std::string actual = task.Solve();

    std::string expected = "(a | !b) & (!a | b) & (!a | !b)";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(LogicalExpressionTest, InvalidDataPCNFCase) {
    ::Tasks::LogicalExpressionTask task("!(a & !b", ::Tasks::TaskTypes::LogicalPCNF);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(LogicalExpressionTest, NoOperatorPCNFCase) {
    ::Tasks::LogicalExpressionTask task("a !b", ::Tasks::TaskTypes::LogicalPCNF);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}
