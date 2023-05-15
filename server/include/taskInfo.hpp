#pragma once

#include <memory>
#include <string>

namespace Tasks {

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
    MatStatSeqInitMoment,
    MatStatSeqCentralMoment,
    MatStatSeqAsymmetry,
    MatStatSeqExcess,
    MatStatSeqQuantile
};

struct TaskInfo {
    TaskInfo(std::string taskData, TaskTypes taskType) : TaskData(std::move(taskData)), TaskType(taskType) {}

    TaskInfo() : TaskType(TaskTypes::NotFound) {}

    std::string TaskData;
    TaskTypes TaskType;
};

}  // namespace Tasks
