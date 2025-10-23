#ifndef CUSTOMRESULTRECORD_H
#define CUSTOMRESULTRECORD_H

#include <ResultRecord.h>
#include "CalcFunctions.h"

class CustomResultRecord : public ResultRecord
{
    Q_OBJECT
public:
    CustomResultRecord(double alpha, CalcFunc::Selector target,
                    std::vector<double> laplace_result, std::vector<std::pair<int, double>> laplace_best,
                    std::vector<double> wald_result, std::vector<std::pair<int, double>> wald_best,
                    std::vector<double> savage_result, std::vector<std::pair<int, double>> savage_best,
                    std::vector<double> gurvitsa_result, std::vector<std::pair<int, double>> gurvitsa_best,
                    const QString& title = "Результат расчета", QWidget* parent = nullptr);

    ~CustomResultRecord() = default;

protected:
    void CreateRecord() override;

private:
    std::vector<double> result;
    std::vector<bool> min_max_sings;

    double alpha;
    QString target;
    std::vector<double> laplace_result;
    std::vector<std::pair<int, double>> laplace_best;
    std::vector<double> wald_result;
    std::vector<std::pair<int, double>> wald_best;
    std::vector<double> savage_result;
    std::vector<std::pair<int, double>> savage_best;
    std::vector<double> gurvitsa_result;
    std::vector<std::pair<int, double>> gurvitsa_best;
};

#endif // CUSTOMRESULTRECORD_H

