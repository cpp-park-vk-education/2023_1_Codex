
#ifndef PROBLEMTYPE_H
#define PROBLEMTYPE_H
#include <QString>
#include <QMap>
#include <QVector>
//int categoriesNum = 9;
//int taskTypesNum = 28;
#include "taskInfo.hpp"

QVector<Client::TaskTypes> taskTypes = {
    Client::NotFound,
    Client::IntegNewton,
    Client::IntegSimpson,
    Client::IntegTrapez,
    Client::CombComb,
    Client::CombRe,
    Client::CombPlace,
    Client::CombPart,
    Client::EqLin,
    Client::EqSq,
    Client::EqPoly,
    Client::EqSGauss,
    Client::EqSGaussM,
    Client::EqSLU,
    Client::Arithmetic,
    Client::DiffSymb,
    Client::DiffNum,
    Client::MatrixDet,
    Client::MatrixT,
    Client::MatrixEigen,
    Client::MatrixRank,
    Client::MatrixNorm,
    Client::MatStatInitMoment,
    Client::MatStatCentralMoment,
    Client::MatStatAsymmetry,
    Client::MatStatExcess,
    Client::MatStatQuantile
};

QMap<QString, QVector<QString>> TaskTypesMap = {
    {"Integrals", {"Mean method","Simpson method","Trapeze method"}},
    {"Combinatorics", {"Combinations","Rearrangements","Placements","Partition"}},
    {"Equations", {"Linear","Squared","Polynomial"}},
    {"Linear Algebraic Equation System", {"Gauss","Gauss with choosing Main element","SLU"}},
    {"Arithmetic", {"Arithmetic"}},
    {"Differentiation",{"Symbolic", "Numerical"}},
    //{"Logical",{"PDNF", "PCNF"}},
    {"Matrix", {"Determinant","Transpare","Eigen values","Rank","Norm"}},
    {"MatStat", {"InitMoment", "CentralMoment","Asymmetry", "Excess","Quantile"}}
};

#endif // PROBLEMTYPE_H
