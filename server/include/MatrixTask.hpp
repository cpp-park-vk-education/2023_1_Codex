#pragma once

#include <map>
#include <string>
#include <vector>

#include "ITask.hpp"
#include "taskInfo.hpp"

#define ROW_FOR_DECOMP 0

namespace Tasks {

class MatrixTask final : public ITask {
   public:
    MatrixTask(std::string expression, TaskTypes taskType);

    std::string Solve() override;

   private:
        void ParseData() override;
        double Determinant();
        std::vector<std::vector<double>> Transpose() const;
        void EigenValuesAndVectors();
        int Rank();
        double Norma();
        std::vector<std::vector<double>> data;
        unsigned cols;
        unsigned rows;

        double countDet(std::vector<std::vector<double>>, unsigned, unsigned) const;
        double countMinor(size_t, size_t, size_t, size_t) const;
        void performElementaryRowOperations(int, int);

        std::vector<double> eigenvalues;
        std::vector<std::vector<double>> eigenvectors;
};

}  // namespace Tasks