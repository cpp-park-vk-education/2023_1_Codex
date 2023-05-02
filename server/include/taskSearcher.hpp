#pragma once

#include <boost/beast/http.hpp>
#include <memory>
#include <string>

#include "ITask.hpp"
#include "ITaskSearcher.hpp"

namespace Handlers {

namespace http = boost::beast::http;  // from <boost/beast/http.hpp>

enum TaskTypes {
    NotFound,
    IntegNewton,
    IntegSimpson,
    IntegTrapez,
    CombComb,
    CombRe,
    CombPlace,
    CombPart,
    EqLin,
    EqSq,
    EqPoly,
    EqSGauss,
    EqSGaussM,
    EqSLU,
    Arithmetic,
    DiffSymb,
    DiffNum,
    MatrixDet,
    MatrixT,
    MatrixEigen,
    MatrixRank,
    MatrixNorm,
    MatStatInitMoment,
    MatStatCentralMoment,
    MatStatAsymmetry,
    MatStatExcess,
    MatStatQuantile
};

struct TaskInfo {
    TaskInfo(std::string taskData, TaskTypes taskType) : TaskData(std::move(taskData)), TaskType(taskType) {}

    TaskInfo() : TaskType(TaskTypes::NotFound) {}

    std::string TaskData;
    TaskTypes TaskType;
};

class TaskSearcher final : public ITaskSearcher {
   public:
    explicit TaskSearcher(std::shared_ptr<std::string const> docRoot);

    ::Tasks::ITaskUPtr Run(http::request<http::dynamic_body> &request) override;

   private:
    TaskInfo DoTaskSearch(http::request<http::dynamic_body> &request) const;

    std::shared_ptr<std::string const> DocRoot;
};

}  // namespace Handlers
