#include "CalcFunctions.h"

#include <algorithm>
#include <QDebug>

std::vector<double> CalcFunc::CriterionLaplace(Matrix<double> &data){

    std::vector<double> result;

    const double probability = std::round(1.0/data.GetColumnsCount()* 100.0) / 100.0;;

    for(int i = 0; i < data.GetRowsCount(); i++){

        double sum =  0.0;
        for(int j = 0; j < data.GetColumnsCount(); j++){
            sum += data[i][j];
        }
        result.push_back(probability * sum);
    }

    return result;
}

std::vector<double> CalcFunc::CriterionWald(Matrix<double> &data,  CalcFunc::Selector selector){

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

std::vector<double> CalcFunc::CriterionSavage(Matrix<double> &data, CalcFunc::Selector selector){
    std::vector<double> result;

    auto matrix_calc = [&data, selector]() -> std::vector<std::vector<double>> {

        std::vector<std::vector<double>> matrix;

        for(int i = 0; i < data.GetColumnsCount(); i++){
            std::vector<double> colum = data.GetColumn(i);
            switch (selector) {
            case Selector::Cost:{
                double min_value = *std::min_element(colum.begin(), colum.end());
                for(int j = 0; j < colum.size(); j++){
                    colum[j] = colum[j] - min_value;
                }
                break;
            }
            case Selector::Profit:{
                double max_value = *std::max_element(colum.begin(), colum.end());
                for(int j = 0; j < colum.size(); j++){
                    colum[j] = max_value - colum[j];
                }
                break;
            }
            }

            matrix.push_back(colum);
        }

        std::vector<std::vector<double>> transposed(matrix[0].size(), std::vector<double>(matrix.size()));

        for (int i = 0; i < matrix.size(); ++i) {
            for (size_t j = 0; j < matrix[0].size(); ++j) {
                transposed[j][i] = matrix[i][j];
            }
        }

        return transposed;
    };

    std::vector<std::vector<double>> risk_matrix = matrix_calc();
    for (int i = 0; i < data.GetRowsCount(); i++) {
        std::vector<double> row = risk_matrix[i];

        double value = *std::max_element(row.begin(), row.end());

        result.push_back(value);
    }

    return result;
}

std::vector<double> CalcFunc::CriterionGurvitsa(Matrix<double> &data, double alpha, CalcFunc::Selector selector){
    std::vector<double> result;

    for (int i = 0; i < data.GetRowsCount(); i++) {
        std::vector<double> row = data.GetRow(i);

        double value_min = *std::min_element(row.begin(), row.end());
        double value_max = *std::max_element(row.begin(), row.end());



        double value;
        switch (selector) {
            case Selector::Cost:{
                value = alpha * value_min + (1 - alpha)*value_max;
                qDebug() << alpha;
                break;
            }
            case Selector::Profit:{
                value = alpha * value_max + (1 - alpha)*value_min;
                break;
            }

        }
        result.push_back(value);
    }

    return result;
}


std::vector<std::pair<int, double>> CalcFunc::BestStrategyLaplace(std::vector<double>& result, CalcFunc::Selector selector){

    std::vector<std::pair<int, double>> best_stratrgy;

    double min_value = *std::min_element(result.begin(), result.end());
    double max_value = *std::max_element(result.begin(), result.end());

    for(int i = 0; i < result.size(); i++){
        switch (selector) {
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

std::vector<std::pair<int, double>> CalcFunc::BestStrategyWald(std::vector<double>& result, CalcFunc::Selector selector){
    std::vector<std::pair<int, double>> best_stratrgy;

    double min_value = *std::min_element(result.begin(), result.end());
    double max_value = *std::max_element(result.begin(), result.end());

    for(int i = 0; i < result.size(); i++){
        switch (selector) {
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
std::vector<std::pair<int, double>> CalcFunc::BestStrategySavage(std::vector<double>& result, CalcFunc::Selector selector){
    std::vector<std::pair<int, double>> best_stratrgy;

    double min_value = *std::min_element(result.begin(), result.end());

    for(int i = 0; i < result.size(); i++){
        if(result[i] == min_value)
            best_stratrgy.push_back(std::pair<int, double>(i, min_value));
    }
    return best_stratrgy;
}
std::vector<std::pair<int, double>> CalcFunc::BestStrategyGurvitsa(std::vector<double>& result, CalcFunc::Selector selector){
    std::vector<std::pair<int, double>> best_stratrgy;

    double min_value = *std::min_element(result.begin(), result.end());
    double max_value = *std::max_element(result.begin(), result.end());

    for(int i = 0; i < result.size(); i++){
        switch (selector) {
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
