
#ifndef PROBLEMTYPE_H
#define PROBLEMTYPE_H
#include <QString>
#include <QMap>
#include <QVector>
//int categoriesNum = 9;
//int taskTypesNum = 28;
#include "taskInfo.hpp"
/*
enum TaskTypes {
    NotFound,
    IntegNewton, //Вычисление интеграла с помощью метода Ньютона
        IntegSimpson,// Интеграл методом Симпсона
        IntegTrapez,// –//– метода трапеций
    CombComb, //Количество сочетаний “2 8”
    CombRe,// Количество перестановок “2 8”
        CombPlace, //размещений “2”
        CombPart, //разбиений “2”
    EqLin, //линейное уравнение
    EqSq, //квадратное уравнение
        EqPoly, //полиномиальное уравнение
        EqSGauss, //слау методом гаусса
        EqSGaussM, //слау методом гаусса с выбором главного элемента
    EqSLU,// LU разложением

    Arithmetic,// арифметика
        DiffSymb,// символьное дифференцирование
    DiffNum, //численное дифференцирование
        LogicalPDNF,//        СДНФ
        LogicalPCNF, //       СКНФ
        MatrixDet,// определитель матрицы
        MatrixT,// транспонирование матрицы
        MatrixEigen,// собственные числа
    MatrixRank, //Ранг
        MatrixNorm, //Норма матрицы

            MatStatInitMoment,
    MatStatCentralMoment,
    MatStatAsymmetry,
    MatStatExcess,
    MatStatQuantile,
    ProblemTypeNum
};*/

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
