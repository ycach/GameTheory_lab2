#include "CustomResultRecord.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

CustomResultRecord::CustomResultRecord(
                    double alpha, CalcFunc::Selector target,
                    std::vector<double> laplace_result, std::vector<std::pair<int, double>> laplace_best,
                    std::vector<double> wald_result, std::vector<std::pair<int, double>> wald_best,
                    std::vector<double> savage_result, std::vector<std::pair<int, double>> savage_best,
                    std::vector<double> gurvitsa_result, std::vector<std::pair<int, double>> gurvitsa_best,
                    const QString& title, QWidget* parent
    )
    : ResultRecord(title, parent),
    laplace_result(laplace_result), laplace_best(laplace_best),
    wald_result(wald_result),  wald_best(wald_best),
    savage_result(savage_result), savage_best(savage_best),
    gurvitsa_result(gurvitsa_result), gurvitsa_best(gurvitsa_best)
{
    this->alpha = alpha;
    if(target == CalcFunc::Selector::Cost){
        this->target = "Затраты";
    }
    if(target == CalcFunc::Selector::Profit){
        this->target = "Прибыль";
    }

}


void CustomResultRecord::CreateRecord(){
    QVBoxLayout* main_layout = new QVBoxLayout(this);

    QString data = QString("Вводные данные: a = %1; Vij - %2;").arg(alpha).arg(target);
    QLabel* label_data = new QLabel(data, this);
    main_layout->addWidget(label_data);


    //laplas
    {
        QVBoxLayout* laplas_layout = new QVBoxLayout();

        QLabel* label_title = new QLabel("\n\n*** Критерий Лапласа ***", this);
        laplas_layout->addWidget(label_title);

        QLabel* label_result = new QLabel("Гарантированные значения:",this);
        laplas_layout->addWidget(label_result);
        {
            int count = 0;
            for(auto elm : laplace_result){
                count++;

                QString strategy_value = QString("\tСтратегия %1: W%1 = %2").arg(count).arg(elm);
                QLabel* result_label_row = new QLabel(strategy_value, this);
                laplas_layout->addWidget(result_label_row);
            }
        }
        QLabel* label_best = new QLabel("Лучшая стратегия:",this);
        laplas_layout->addWidget(label_best);
        {
            for(auto best : laplace_best){

                QString strategy_value = QString("\tСтратегия %1: значение: %2").arg(best.first + 1).arg(best.second);
                QLabel* result_label_row = new QLabel(strategy_value, this);
                laplas_layout->addWidget(result_label_row);
            }
        }

        main_layout->addLayout( laplas_layout);
    }

    //wald
    {
        QVBoxLayout* wald_layout = new QVBoxLayout();
        QLabel* label_title = new QLabel("\n\n*** Критерий Вальда ***", this);
        wald_layout->addWidget(label_title);

        QLabel* label_result = new QLabel("Экстремальные значения:",this);
        wald_layout->addWidget(label_result);
        {
            int count = 0;
            for(auto elm : wald_result){
                count++;

                QString strategy_value = QString("\tСтратегия %1: значение: %2").arg(count).arg(elm);
                QLabel* result_label_row = new QLabel(strategy_value, this);
                wald_layout->addWidget(result_label_row);
            }
        }
        QLabel* label_best = new QLabel("Лучшая стратегия:",this);
        wald_layout->addWidget(label_best);
        {
            for(auto best : wald_best){

                QString strategy_value = QString("\tСтратегия %1: значение: %2").arg(best.first + 1).arg(best.second);
                QLabel* result_label_row = new QLabel(strategy_value, this);
                wald_layout->addWidget(result_label_row);
            }
        }

        main_layout->addLayout(wald_layout);
    }

    //savage
    {
        QVBoxLayout* savage_layout = new QVBoxLayout();
        QLabel* label_title = new QLabel("\n\n*** Критерий Сэвиджа ***", this);
        savage_layout->addWidget(label_title);

        QLabel* label_result = new QLabel("Максимальные значения матрицы сожалений:",this);
        savage_layout->addWidget(label_result);
        {
            int count = 0;
            for(auto elm : savage_result){
                count++;

                QString strategy_value = QString("\tСтратегия %1: max[r_ij] = %2").arg(count).arg(elm);
                QLabel* result_label_row = new QLabel(strategy_value, this);
                savage_layout->addWidget(result_label_row);
            }
        }
        QLabel* label_best = new QLabel("Лучшая стратегия:",this);
        savage_layout->addWidget(label_best);
        {
            for(auto best : savage_best){

                QString strategy_value = QString("\tСтратегия %1: значение: %2").arg(best.first+ 1).arg(best.second);
                QLabel* result_label_row = new QLabel(strategy_value, this);
                savage_layout->addWidget(result_label_row);
            }
        }

        main_layout->addLayout(savage_layout);
    }

    //gurvitsa
    {
        QVBoxLayout* gurvitsa_layout = new QVBoxLayout();
        QLabel* label_title = new QLabel("\n\n*** Критерий Гурвица ***", this);
        gurvitsa_layout->addWidget(label_title);

        QLabel* label_result = new QLabel("Значения по Гурвицу:",this);
        gurvitsa_layout->addWidget(label_result);
        {
            int count = 0;
            for(auto elm : gurvitsa_result){
                count++;

                QString strategy_value = QString("\tСтратегия %1: значение: %2").arg(count).arg(elm);
                QLabel* result_label_row = new QLabel(strategy_value, this);
                gurvitsa_layout->addWidget(result_label_row);
            }
        }
        QLabel* label_best = new QLabel("Лучшая стратегия:",this);
        gurvitsa_layout->addWidget(label_best);
        {
            for(auto best : gurvitsa_best){

                QString strategy_value = QString("\tСтратегия %1: значение: %2").arg(best.first + 1).arg(best.second);
                QLabel* result_label_row = new QLabel(strategy_value, this);
                gurvitsa_layout->addWidget(result_label_row);
            }
        }

        main_layout->addLayout(gurvitsa_layout);
    }
}
