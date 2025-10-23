#ifndef CALCFUNCTIONS_H
#define CALCFUNCTIONS_H

#include <vector>

#include "MatrixData/Matrix.h"

namespace CalcFunc {
    enum Selector{
        Cost,
        Profit
    };

    std::vector<double> CriterionLaplace(Matrix<double> &data);
    std::vector<double> CriterionWald(Matrix<double> &data, CalcFunc::Selector selector = Selector::Cost);
    std::vector<double> CriterionSavage(Matrix<double> &data, CalcFunc::Selector selector = Selector::Cost);
    std::vector<double> CriterionGurvitsa(Matrix<double> &data, double alpha = 0.4, CalcFunc::Selector selector = Selector::Cost);

    std::vector<std::pair<int, double>> BestStrategyLaplace(std::vector<double>& result, CalcFunc::Selector selector = Selector::Cost);
    std::vector<std::pair<int, double>> BestStrategyWald(std::vector<double>& result, CalcFunc::Selector selector = Selector::Cost);
    std::vector<std::pair<int, double>> BestStrategySavage(std::vector<double>& result, CalcFunc::Selector selector = Selector::Cost);
    std::vector<std::pair<int, double>> BestStrategyGurvitsa(std::vector<double>& result, CalcFunc::Selector selector = Selector::Cost);
}
#endif // CALCFUNCTIONS_H
