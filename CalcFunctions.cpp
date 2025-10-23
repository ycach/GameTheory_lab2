#include "CalcFunctions.h"

#include <algorithm>


std::vector<double> CalcFunc::CriterionLaplace(Matrix<double> data,  Selector selector){

    std::vector<double> result;

    const double probability = 1/data.GetColumnsCount();

    for(int i = 0; i < data.GetRowsCount(); i++){

        double sum =  0.0;
        for(j = 0; j < data.GetColumnsCount(); j++){
            sum += data[i][j];
        }
        result.push_back(probability * sum);
    }

    for(auto item : result){

    }

    return result;
}

std::vector<std::pair<int, double>> CalcFunc::CriterionWald(Matrix<double> data,  Selector selector){

    std::vector<double> result;

    for (int i = 0; i < data.GetRowsCount(); i++) {
        std::vector<double> row = data.GetRow(i);

        if (row.empty()) continue;

        double value;
        switch (selector) {
        case Selector::Cost:
        {
            auto it = std::max_element(row.begin(), row.end());
            value = *it;
        }
        break;
        case Selector::Profit:
        {
            auto it = std::min_element(row.begin(), row.end());
            value = *it;
        }
        break;
        }
        result.push_back(value);
    }

    return result;
}

std::vector<double> CalcFunc::CriterionSavage(Matrix<double> data, Selector = Selector::Cost){
    std::vector<double> result;

    for (int i = 0; i < data.GetRowsCount(); i++) {
        std::vector<double> row = data.GetRow(i);

        if (row.empty()) continue;

        double value;
        switch (selector) {
        case Selector::Cost:
        {
            auto it = std::min_element(row.begin(), row.end());
            value = *it;
        }
        break;
        case Selector::Profit:
        {
            auto it = std::max_element(row.begin(), row.end());
            value = *it;
        }
        break;
        }
        result.push_back(value);
    }

    return result;
}

std::vector<double> CalcFunc::CriterionGurvitsa(Matrix<double> data, double alpha = 0.4, Selector = Selector::Cost){
    std::vector<double> result;

    for (int i = 0; i < data.GetRowsCount(); i++) {
        std::vector<double> row = data.GetRow(i);

        if (row.empty()) continue;

        auto it_min = std::min_element(row.begin(), row.end());
        double value_min = *it_min;

        auto it_max = std::max_element(row.begin(), row.end());
        double value_max = *it_max;

        double value;
        switch (selector) {
        case Selector::Cost:
        {
            value = alpha * value_min + (1 -alpha)*value_max;
        }
        break;
        case Selector::Profit:
        {
            value = alpha * value_max + (1 -alpha)*value_min;
        }
        break;
        }
        result.push_back(value);
    }

    return result;
}


std::vector<std::pair<int, double>> CalcFunc::BestStrategyLaplace(std::vector<double>& result, selector = Selector::Cost){

    std::vector<std::pair<int, double>> best_stratrgy;

    double min_value = *std::min_element(result.begin(), result.end());
    double max_value = *std::max_element(result.begin(), result.end());

    for(int i = 0; i < result.size(); i++){
        switch (Selector) {
        case Selector::Cost:
            if(result[i] == min_value)
                best_stratrgy.push_back(std::pair<int, double>(i, min_value));
            break;
        case Selector::Profit:
            if(result[i] == max_value)
                best_stratrgy.push_back(std::pair<int, double>(i, max_value));
            break;
        }
    }
    return best_stratrgy;
}

std::vector<std::pair<int, double>> CalcFunc::BestStrategyWald(std::vector<double>& result, selector = Selector::Cost){
    std::vector<std::pair<int, double>> best_stratrgy;

    double min_value = *std::min_element(result.begin(), result.end());
    double max_value = *std::max_element(result.begin(), result.end());

    for(int i = 0; i < result.size(); i++){
        switch (Selector) {
        case Selector::Cost:
            if(result[i] == min_value)
                best_stratrgy.push_back(std::pair<int, double>(i, min_value));
            break;
        case Selector::Profit:
            if(result[i] == max_value)
                best_stratrgy.push_back(std::pair<int, double>(i, max_value));
            break;
        }
    }
    return best_stratrgy;
}
std::vector<std::pair<int, double>> CalcFunc::BestStrategySavage(std::vector<double>& result, selector = Selector::Cost){
    std::vector<std::pair<int, double>> best_stratrgy;

    double min_value = *std::min_element(result.begin(), result.end());

    for(int i = 0; i < result.size(); i++){
        if(result[i] == min_value)
            best_stratrgy.push_back(std::pair<int, double>(i, min_value));
    }
    return best_stratrgy;
}
std::vector<std::pair<int, double>> CalcFunc::BestStrategyGurvitsa(std::vector<double>& result, selector = Selector::Cost){
    std::vector<std::pair<int, double>> best_stratrgy;

    double min_value = *std::min_element(result.begin(), result.end());

    for(int i = 0; i < result.size(); i++){
        switch (Selector) {
        case Selector::Cost:
            if(result[i] == min_value)
                best_stratrgy.push_back(std::pair<int, double>(i, min_value));
            break;
        case Selector::Profit:
            if(result[i] == max_value)
                best_stratrgy.push_back(std::pair<int, double>(i, max_value));
            break;
        }
    }
    return best_stratrgy;
}
