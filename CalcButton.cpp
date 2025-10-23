#include "CalcButton.h"
#include "CalcFunctions.h"

#include "CustomRecord/CustomResultRecord.h"



CalcButton::CalcButton(DinamicTable* table, ResultWindow* result_window, QDoubleSpinBox* alpha_box, QComboBox* selector_box, QString text, QWidget* parent) : QPushButton(text, parent) {
    lock = false;
    this->table_data = table;
    this->result_window = result_window;
    this->alpha_spin = alpha_box;
    this->combo_box = selector_box;

    connect(table, &DinamicTable::ErrorGetData, this, &CalcButton::Lock);
    connect(this, &QPushButton::clicked, this, &CalcButton::Calculate);
}


void CalcButton::Lock(){
    lock = true;
}
void CalcButton::Unlock(){
    lock = false;
}

void CalcButton::Calculate(){
    Matrix<double> data = table_data->GetData();
    double alpha = alpha_spin->value();
    int value = combo_box->currentIndex();
    CalcFunc::Selector selector;
    if(value == 0)
        selector = CalcFunc::Selector::Cost;
    else
        selector = CalcFunc::Selector::Profit;

    if(!lock){
        std::vector<double> laplace_result = CalcFunc::CriterionLaplace(data);
        std::vector<double> wald_result = CalcFunc::CriterionWald(data, selector);
        std::vector<double> savage_result = CalcFunc::CriterionSavage(data, selector);
        std::vector<double> gurvitsa_result = CalcFunc::CriterionGurvitsa(data, alpha, selector);

        std::vector<std::pair<int, double>> laplace_best = CalcFunc::BestStrategyLaplace(laplace_result, selector);
        std::vector<std::pair<int, double>> wald_best =  CalcFunc::BestStrategyWald(wald_result, selector);
        std::vector<std::pair<int, double>> savage_best = CalcFunc::BestStrategySavage(savage_result, selector);
        std::vector<std::pair<int, double>> gurvitsa_best = CalcFunc::BestStrategyGurvitsa(gurvitsa_result, selector);

        CustomResultRecord* new_record = new CustomResultRecord(
            alpha, selector,
            laplace_result, laplace_best,
            wald_result, wald_best,
            savage_result, savage_best,
            gurvitsa_result, gurvitsa_best,
            "Результат расчета", result_window
            );
        result_window->AddRecord(new_record);
    }
    lock = false;
}
