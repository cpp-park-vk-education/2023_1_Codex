#pragma once

#include <memory>
#include <string>

namespace Tasks {

class ITask {
   public:
    virtual ~ITask() {}

    virtual std::string Solve() = 0;

    std::string GetExpression() const {
        return Expression;
    }

    std::string GetTaskType() const {
        return TaskType;
    }

   private:
    virtual void ParseData() = 0;

    std::string Expression;
    std::string TaskType;
};

using ITaskUPtr = std::unique_ptr<ITask>;

}  // namespace Tasks