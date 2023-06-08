#pragma once

#include <string>

namespace Client {

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
    DiffNum,
    MatrixDet,
    MatrixT,
    MatrixEigen,
    MatrixRank,
    MatrixNorm,
    MatStatSeqInitMoment,
    MatStatSeqCentralMoment,
    MatStatSeqAsymmetry,
    MatStatSeqExcess,
    MatStatSeqQuantile
};

struct TaskInfo {
    TaskInfo(std::string taskData, TaskTypes taskType, std::string taskAnswer, std::string taskError = "",
             bool errorCode = false)
        : TaskData(std::move(taskData)),
          TaskType(taskType),
          TaskAnswer(std::move(taskAnswer)),
          TaskError(std::move(taskError)),
          ErrorCode(errorCode) {}

    TaskInfo() : TaskType(TaskTypes::NotFound), ErrorCode(false) {}

    std::string TaskData;
    TaskTypes TaskType;
    std::string TaskAnswer;
    std::string TaskError;
    bool ErrorCode;
};

}  // namespace Client
