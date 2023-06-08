#pragma once

#include <string>
#include <vector>

#include "ITask.hpp"
#include "taskInfo.hpp"

namespace Tasks {

class EqSystemTask final : public ITask {
   public:
    EqSystemTask(const std::string expression, TaskTypes taskType);

    std::string Solve() override;

   private:
    void ParseData() override;

    std::vector<std::vector<double>> A;
    std::vector<double> B;

    std::string VectorToString(const std::vector<double>& nums);

    std::vector<double> Gaussian();
    std::vector<double> GaussianMainEl();
    std::vector<double> LU();
};

}  // namespace Tasks