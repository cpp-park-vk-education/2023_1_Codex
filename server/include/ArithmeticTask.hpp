#pragma once

#include <string>

#include "ITask.hpp"

namespace Tasks {

class ArithmeticTask final : public ITask {
   public:
    ArithmeticTask(std::string expression, TaskTypes taskType);

    std::string Solve() override;

   private:
    void ParseData() override;
};

}  // namespace Tasks