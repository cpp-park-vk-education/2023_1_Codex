#pragma once

#include <string>

#include "IMatStatTask.hpp"
#include "taskInfo.hpp"

namespace Tasks {

class MatStatSequenceTask final : public IMatStatTask {
   public:
    MatStatSequenceTask(std::string expression, TaskTypes taskType);

    std::string Solve() override;

private:
    void ParseData() override;
    double InitialMoment() override;
    double CentralMoment() override;
    double Asymmetry() override;
    double Excess() override;

    double Quantile();
};

}  // namespace Tasks