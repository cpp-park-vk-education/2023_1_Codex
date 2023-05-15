#pragma once

#include <string>

#include "ITask.hpp"

namespace Tasks {

class DifferentiationTask final : public ITask {
   public:
    DifferentiationTask(std::string expression, TaskTypes taskType);

    std::string Solve() override;

   private:
    void ParseData() override;

    double Numerical();
    double Symbolic();
};

}  // namespace Tasks