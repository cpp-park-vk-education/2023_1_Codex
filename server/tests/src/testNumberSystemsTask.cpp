#include <gtest/gtest.h>

#include <string>

#include "exceptions.hpp"
#include "NumberSystems.hpp"
#include "taskInfo.hpp"

TEST(NumberSystemsTest, BasicCase){
    ::Tasks::NumberSystemsTask task("11101 2 10", ::Tasks::TaskTypes::NumberSystems);
    std::string actual = task.Solve();

    std::string expected = "29";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(NumberSystemsTest, LeadingZerosCase){
    ::Tasks::NumberSystemsTask task("00011101 2 10", ::Tasks::TaskTypes::NumberSystems);
    std::string actual = task.Solve();

    std::string expected = "29";
    EXPECT_STREQ(expected.c_str(), actual.c_str());
}

TEST(NumberSystemsTest, InvalidDataCase){
    // недопустимые символы
    ::Tasks::NumberSystemsTask task("11101o1 2 8", ::Tasks::TaskTypes::NumberSystems);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(NumberSystemsTest, InvalidBaseSystemCase){
    // числа с основанием 2 могут содержать только цифры <2
    ::Tasks::NumberSystemsTask task("345123 2 8", ::Tasks::TaskTypes::NumberSystems);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}

TEST(NumberSystemsTest, NotEnoughArgsCase){
    // недостаточно аргументов
    ::Tasks::NumberSystemsTask task("11101 2", ::Tasks::TaskTypes::NumberSystems);

    EXPECT_THROW(task.Solve(), ::Tasks::TaskInvalidData);
}
