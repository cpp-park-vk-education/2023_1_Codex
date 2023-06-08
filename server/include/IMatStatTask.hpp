#pragma once

#include <string>

#include "ITask.hpp"

namespace Tasks {

class IMatStatTask : public ITask {
   public:
    virtual ~IMatStatTask() {}

   protected:
    virtual double InitialMoment(double degree) = 0;
    virtual double CentralMoment(double degree) = 0;
    virtual double Asymmetry() = 0;
    virtual double Excess() = 0;
};

}  // namespace Tasks
