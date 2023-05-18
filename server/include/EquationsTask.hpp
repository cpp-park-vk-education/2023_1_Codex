#pragma once

#include <string>
#include <vector>

#include "ITask.hpp"
#include "taskInfo.hpp"

namespace Tasks {

class EquationsTask final : public ITask {
   public:
    EquationsTask(const std::string expression, TaskTypes taskType);

    std::string Solve() override;

   private:
    void ParseData() override;

    std::vector<double> Numbers;

    double SimpleLinear();
    std::vector<double> Square();
    void Polynomial();
};

}  // namespace Tasks