#pragma once

#include <string>

#include "ITask.hpp"

namespace Tasks {

class IntegrationTask final : public ITask {
   public:
    IntegrationTask(const std::string expression, TaskTypes taskType);

    std::string Solve() override;

   private:
    void ParseData() override;

    double NewtonCotes();
    double Simpson();
    double Trapezoid();
};

}  // namespace Tasks