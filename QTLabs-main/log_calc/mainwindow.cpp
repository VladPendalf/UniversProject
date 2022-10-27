#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    my_func();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_LogOp_currentIndexChanged(int ) // Выбор операции
{

    switch (ui->comboBox_LogOp->currentIndex())
    {
    case 0: // and
        MainWindow::on_comboBox_OP1_currentIndexChanged( ui->comboBox_OP1->currentIndex());
        MainWindow::on_comboBox_OP2_currentIndexChanged( ui->comboBox_OP2->currentIndex());// вызов значений с кнопок
        break;
    case 1: //or
        MainWindow::on_comboBox_OP1_currentIndexChanged( ui->comboBox_OP1->currentIndex());
        MainWindow::on_comboBox_OP2_currentIndexChanged( ui->comboBox_OP2->currentIndex());// вызов значений с кнопок
        break;
    case 2: //!
        MainWindow::on_comboBox_OP1_currentIndexChanged( ui->comboBox_OP1->currentIndex());
        MainWindow::on_comboBox_OP2_currentIndexChanged( ui->comboBox_OP2->currentIndex());// вызов значений с кнопок
        break;
    case 3: //!or
        MainWindow::on_comboBox_OP1_currentIndexChanged( ui->comboBox_OP1->currentIndex());
        MainWindow::on_comboBox_OP2_currentIndexChanged( ui->comboBox_OP2->currentIndex());// вызов значений с кнопок
        break;
    case 4: // ->
        MainWindow::on_comboBox_OP1_currentIndexChanged( ui->comboBox_OP1->currentIndex());
        MainWindow::on_comboBox_OP2_currentIndexChanged( ui->comboBox_OP2->currentIndex());// вызов значений с кнопок
        break;
    case 5: // ==
        MainWindow::on_comboBox_OP1_currentIndexChanged( ui->comboBox_OP1->currentIndex());
        MainWindow::on_comboBox_OP2_currentIndexChanged( ui->comboBox_OP2->currentIndex());// вызов значений с кнопок
        break;
    }
}

void MainWindow::on_comboBox_OP1_currentIndexChanged(int index) // Считывание значения с первой кнопки
{

    switch (index)
    {
    case 0:
        my_func();
        break;
    case 1:
        my_func();
        break;
    }
}

void MainWindow::on_comboBox_OP2_currentIndexChanged(int index) // Считывание значения со второй кнопки
{
    switch (index)
    {
    case 0:
        my_func();
        break;
    case 1:
        my_func();
        break;
    }
}

void MainWindow::my_func() // если 1 кнопка == 0
{
    int LogOp; bool Op1, Op2, res;

    LogOp = ui->comboBox_LogOp->currentIndex();
    Op1 = ui->comboBox_OP1->currentIndex();
    Op2 = ui->comboBox_OP2->currentIndex();

    /* 0 -> 1 & 1 == 1, 1 & 0 || 0 & 1 == 0
       1 -> 1 || 0, 0 || 1, 1 || 1 == 1
       2 -> !1 == 0, !0 == 1
       3 -> 0 != 1 == 0,
       4 -> 1 -> 0 == 0, else 1
       5 ->1 == 1 & 0 == 0, == 1
    */

    QPalette pal;
    pal=ui->centralWidget->palette(); //считали палитру
    switch (LogOp)
    {
    case 0: // and
        ui->comboBox_OP2->setVisible(true);
        if ((Op1 == 1) && (Op2 == 1))
            res  = true;
        else
            res = false;
        break;
    case 1:// or
        ui->comboBox_OP2->setVisible(true);
        if ((Op2 == 1) || (Op1 == 1))
            res = true;
        else
            res = false;
        break;
    case 2:// !
        ui->comboBox_OP2->setVisible(false);
        if (Op1 == 1)
            res = true;
        else
            res = false;
        break;
    case 3:// !=
        ui->comboBox_OP2->setVisible(true);
        if ((Op1 != Op2) || (Op2 != Op1))
            res = true;
        else
            res = false;
        break;
    case 4:// ->
        ui->comboBox_OP2->setVisible(true);
        if((Op1 == 1) && (Op2 == 0))
            res = false;
        else
            res = true;
        break;
    case 5:// ==
        ui->comboBox_OP2->setVisible(true);
        if ((Op2 == Op1) || (Op1 == Op2))
            res = true;
        else
            res = false;
        break;
    }
    if (res)
    {
        pal.setColor(QPalette::Window,Qt::green);
        ui->centralWidget->setAutoFillBackground(true); //разрешаем автозаливку
        ui->centralWidget->setPalette(pal); //присваиваем измененную палитру
    }
    else
    {
        pal.setColor(QPalette::Window,Qt::red);
        ui->centralWidget->setAutoFillBackground(true); //разрешаем автозаливку
        ui->centralWidget->setPalette(pal); //присваиваем измененную палитру
    }
}
