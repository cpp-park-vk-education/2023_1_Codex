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
    std::string expr;

    double get_f_x(const std::string expr, double x);
    double get_f_derivative(const std::string f, double x);

    double SimpleLinear();
    std::vector<double> Square();
    double Polynomial(); // приближенное нахождение корня
};

}  // namespace Tasks