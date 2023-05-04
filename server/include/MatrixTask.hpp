#pragma once

#include <map>
#include <string>
#include <vector>

#include "ITask.hpp"

namespace Tasks {

class MatrixTask final : public ITask {
   public:
    MatrixTask(std::string expression, TaskTypes taskType);

    std::string Solve() override;

   private:
    void ParseData() override;

    double Determinant();
    std::vector<std::vector<double>> Transpose();
    std::map<double, vector<double>> EigenValuesAndVectors();
    int Rank();
    int Norma();

    std::vector<std::vector<double>> data;
};

}  // namespace Tasks