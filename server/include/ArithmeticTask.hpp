#pragma once

#include <memory>
#include <stack>
#include <string>
#include <unordered_set>
#include <vector>

#include "Calculations.hpp"
#include "ITask.hpp"
#include "TaskInfo.hpp"

const std::unordered_set<std::string> operators_set{"+",  "-",   "*",   "/",    "sin", "asin", "cos", "acos",
                                                    "tg", "atg", "ctg", "actg", "exp", "abs",  "^",   "sqrt"};

namespace Tasks {

class ArithmeticTask final : public ITask {
   public:
    ArithmeticTask(std::string expression, TaskTypes taskType);

    std::string Solve() override;

    double Solve_d();

   private:
    void ParseData() override;
    std::vector<std::string> get_lexems();
    void analyze_operator(std::string op);

    std::stack<std::unique_ptr<ICalculatable>> output;
    std::unique_ptr<ICalculatable> root;
};

}  // namespace Tasks
