#pragma once

#include <string>
#include <vector>

#include "IMatStatTask.hpp"
#include "TaskInfo.hpp"

namespace Tasks {

class MatStatSequenceTask final : public IMatStatTask {
   public:
    MatStatSequenceTask(std::string expression, TaskTypes taskType);

    std::string Solve() override;

   private:
    void ParseData() override;
    double InitialMoment(double degree) override;
    double CentralMoment(double degree) override;
    double Asymmetry() override;
    double Excess() override;

    double Quantile();

    std::vector<double> Numbers;
    double Degree;
};

}  // namespace Tasks
