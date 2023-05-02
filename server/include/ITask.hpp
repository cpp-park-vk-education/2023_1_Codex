#pragma once

#include <memory>
#include <string>

namespace Tasks {

class ITask {
   public:
    virtual ~ITask() {}

    virtual std::string Solve() = 0;

    std::string GetExpression() {
        return expression;
    }

   private:
    std::string expression;
};

using ITaskUPtr = std::unique_ptr<ITask>;

}  // namespace Tasks
