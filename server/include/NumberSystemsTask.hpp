#pragma once

#include <string>

#include "ITask.hpp"
#include "TaskInfo.hpp"

namespace Tasks {

class NumberSystemsTask final : public ITask {
   public:
    NumberSystemsTask(std::string expression, TaskTypes taskType);

    std::string Solve() override;

   private:
    std::string expression;
    void ParseData() override;
};

}  // namespace Tasks