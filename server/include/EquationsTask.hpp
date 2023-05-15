#pragma once

#include <string>

#include "ITask.hpp"
#include "taskInfo.hpp"
namespace Tasks {

class EquationsTask final : public ITask {
   public:
    EquationsTask(const std::string expression, TaskTypes taskType);

    std::string Solve() override;

   private:
    void ParseData() override;

    int SimpleLinear();
    int Square();
    int Polynomial();
};

}  // namespace Tasks