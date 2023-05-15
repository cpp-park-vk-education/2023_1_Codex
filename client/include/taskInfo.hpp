#pragma once

#include <string>

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
    TaskInfo(std::string taskData, TaskTypes taskType, std::string taskAnswer)
        : TaskData(std::move(taskData)), TaskType(taskType), TaskAnswer(std::move(taskAnswer)) {}

    TaskInfo() : TaskType(TaskTypes::NotFound) {}

    std::string TaskData;
    TaskTypes TaskType;
    std::string TaskAnswer;
};
