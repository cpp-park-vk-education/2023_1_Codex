#pragma once

#include <string>

#include "ITask.hpp"
#include "taskInfo.hpp"
namespace Tasks {

class CombinatoricsTask final : public ITask {
   public:
    CombinatoricsTask(const std::string expression, TaskTypes taskType);

    std::string Solve() override;

   private:
    void ParseData() override;

    int Combinations();
    int Reshuffle();
    int Placements();
    int Partitioning();
};

}  // namespace Tasks