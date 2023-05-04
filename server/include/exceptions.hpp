#pragma once

#include <exception>
#include <memory>
#include <string>



namespace Tasks {

class TaskException : public std::exception {
   public:
    explicit TaskException(std::string msg) : Msg(std::move(msg)) {}

    const char *what() const noexcept override {
        return Msg.c_str();
    }

   private:
    std::string Msg;
};

class TaskInvalidData : public TaskException {
   public:
    explicit TaskInvalidData(std::string &msg) : TaskException(msg) {}
};

}  // namespace Tasks
