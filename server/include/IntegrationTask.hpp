#pragma once

#include <string>

#include "ITask.hpp"
#include "taskInfo.hpp"

namespace Tasks {

class IntegrationTask final : public ITask {
   public:
    IntegrationTask(const std::string expression, TaskTypes taskType);

    std::string Solve() override;

   private:
    double f(std::string expr, double x);

    std::string expr;
    int n;
    double a, b;

    void ParseData() override;
    double NewtonCotes();
    double Simpson();
    double Trapezoid();
};

}  // namespace Tasks