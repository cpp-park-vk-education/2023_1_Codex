#pragma once

#include <string>

#include "TaskInfo.hpp"

namespace Handlers {

class PredictionConverter {
   public:
    PredictionConverter() = delete;
    PredictionConverter(PredictionConverter &) = delete;
    PredictionConverter &operator=(const PredictionConverter &) = delete;

    static std::string ConvertRecognizerPrediction(const std::string &prediction,
                                                   ::Tasks::TaskTypes taskType);

   private:
    static std::string ConvertMatStatTask(const std::string &prediction);
    static std::string ConvertArithmeticTask(const std::string &prediction);
};

}  // namespace Handlers
