#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "DinamicTable.h"
#include "ResultShower/resultwindow.h"
#include "CalcButton.h"

#include <QPushButton>
#include <QComboBox>
#include <QDoubleSpinBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    DinamicTable* data_table = new DinamicTable(4, 4, 2, 1, this);

    QHBoxLayout* parametrs_layout = new QHBoxLayout();

    QDoubleSpinBox* alpha_spin = new QDoubleSpinBox(this);
    alpha_spin->setRange(0.0, 1.0);
    alpha_spin->setSingleStep(0.01);
    alpha_spin->setDecimals(2);
    alpha_spin->setValue(0.4);

    QComboBox* selector_box = new QComboBox(this);
    selector_box->addItem("Затраты");
    selector_box->addItem("Прибыль");

    parametrs_layout->addWidget(alpha_spin);
    parametrs_layout->addWidget(selector_box);


    ResultWindow* result_window = new ResultWindow("Окно результата", this);

    CalcButton* calc_button = new CalcButton(data_table, result_window, alpha_spin, selector_box, "Рассчитать", this);

    ui->main_layout->addWidget(data_table);
    ui->main_layout->addLayout(parametrs_layout);
    ui->main_layout->addWidget(calc_button);
    ui->main_layout->addWidget(result_window);



}

MainWindow::~MainWindow()
{
    delete ui;
}
