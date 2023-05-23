#pragma once
#include <QHash>
#include <QString>
#include <QVector>

#include "TaskInfo.hpp"

QHash<QString, QVector<QString>> TaskTypesMap = {
    {"Integrals", QVector<QString>() << "Mean method"
                                     << "Simpson method"
                                     << "Trapeze method"},
    {"Combinatorics", QVector<QString>() << "Combinations"
                                         << "Rearrangements"
                                         << "Placements"
                                         << "Partition"},
    {"Equations", QVector<QString>() << "Linear"
                                     << "Squared"
                                     << "Polynomial"},
    {"Linear Algebraic Equation System", QVector<QString>() << "Gauss"
                                                            << "Gauss with choosing Main element"
                                                            << "SLU"},
    {"Arithmetic", QVector<QString>() << "Arithmetic"},
    {"Differentiation", QVector<QString>() << "Symbolic"
                                           << "Numerical"},
    {"Matrix", QVector<QString>() << "Determinant"
                                  << "Transpare"
                                  << "Eigen values"
                                  << "Rank"
                                  << "Norm"},
    {"Logical", QVector<QString>() << "PDNF"
                                   << "PCNF"},
    {"MatStat", QVector<QString>() << "InitMoment"
                                   << "CentralMoment"
                                   << "Asymmetry"
                                   << "Excess"
                                   << "Quantile"}

};

QVector<QString> TaskTypesGlobalNames = {
    "Integrals",  "Combinatorics",   "Equations", "Linear Algebraic Equation System",
    "Arithmetic", "Differentiation", "Matrix",    "Logical",
    "MatStat"};
