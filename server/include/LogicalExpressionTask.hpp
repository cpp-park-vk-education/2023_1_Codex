#pragma once

#include <string>

#include "ITask.hpp"
#include "taskInfo.hpp"

namespace Tasks{

    class LogicalExpressionTask final : public ITask{
    public:
        LogicalExpressionTask(std::string expression, TaskTypes taskType);

        std::string Solve() override;

    private:
        std::string expression;
        void ParseData() override;
        std::string PDNF();
        std::string PCNF();
    };

}  // namespace Tasks