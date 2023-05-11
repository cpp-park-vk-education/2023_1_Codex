#pragma once

#include <string>

#include "ITask.hpp"

namespace Tasks {

class IMatStatTask : public ITask {
   public:
    virtual ~IMatStatTask() {}

protected:
    virtual double InitialMoment() = 0;
    virtual double CentralMoment() = 0;
    virtual double Asymmetry() = 0;
    virtual double Excess() = 0;
};

}  // namespace Tasks
