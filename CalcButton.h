#ifndef CALCBUTTON_H
#define CALCBUTTON_H

#include <QPushButton>
#include <QComboBox>
#include <QDoubleSpinBox>

#include "DinamicTable.h"
#include "ResultShower/ResultWindow.h"

class CalcButton : public QPushButton
{
    Q_OBJECT
public:
    CalcButton(DinamicTable* table, ResultWindow* result_window, QDoubleSpinBox* alpha, QComboBox* selector_box, QString text = "Рассчитать", QWidget* parent = nullptr);

private slots:
    void Calculate();

private:
    DinamicTable* table_data;
    ResultWindow* result_window;
    QDoubleSpinBox* alpha_spin;
    QComboBox* combo_box;
    bool lock;
    void Lock();
    void Unlock();
};

#endif // CALCBUTTON_H
