#pragma once

#include <iomanip>
#include <memory>
#include <string>

#include "taskInfo.hpp"

namespace Tasks {

class ITask {
   public:
    virtual ~ITask() {}

    virtual std::string Solve() = 0;

    std::string GetExpression() const {
        return Expression;
    }

    unsigned GetTaskType() const {
        return TaskType;
    }

   protected:
    virtual void ParseData() = 0;

    std::string DoubleToString(double x) {
        std::stringstream stream;
        stream << std::fixed << std::setprecision(5) << x;

        return stream.str();
    }

    std::string Expression;
    TaskTypes TaskType;
};

using ITaskUPtr = std::unique_ptr<ITask>;

}  // namespace Tasks
