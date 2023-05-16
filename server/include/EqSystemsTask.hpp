#pragma once

#include <string>

#include "ITask.hpp"
#include "taskInfo.hpp"
namespace Tasks {

class EqSystemTask final : public ITask {
   public:
    EqSystemTask(const std::string expression, TaskTypes taskType);

    std::string Solve() override;

   private:
    void ParseData() override;

    int Gaussian();
    int GaussianMainEl();
    int LU();
};

}  // namespace Tasks