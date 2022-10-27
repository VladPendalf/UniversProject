#include "widget.h"
#include "ui_widget.h"
#include <math.h>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->errorlabel->setVisible(false);
    ui->resultLabel->setVisible(false);
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_mul_clicked()//ф-ия деление
{
       ui->labelOp1->setText("Множитель 1");//изменение окна "operand_1" на "Множитель 1"
       ui->labelOp2->setText("Множитель 2");//изменение окна "operand_1" на "Множитель 1"
       ui->resbutton->setText("Произведение");//изменение окна "resultlabel" на "Произведение"
       ui->errorlabel->setVisible(false);//обнуление окна "errorlabel"
       ui->resultLabel->setVisible(false);//обнуление окна "resultlabel"
}


void Widget::on_sum_clicked()//ф-ия суммирования
{
    ui->labelOp1->setText("Слагаемое 1");//изменение окна "operand_1" на "Слагаемое 1"
    ui->labelOp2->setText("Слагаемое 2");//изменение окна "operand_1" на "Слагаемое 2"
    ui->resbutton->setText("Сумма");//изменение окна "resultlabel" на "Сумма"
    ui->errorlabel->setVisible(false);//обнуление окна "errorlabel"
    ui->resultLabel->setVisible(false);//обнуление окна "errorlabel"
}

void Widget::on_div_clicked()//ф-ия умножения
{
    ui->labelOp1->setText("Делимое");//изменение окна "operand_1" на "Делимоe"
    ui->labelOp2->setText("Делитель");//изменение окна "operand_1" на "Делитель"
    ui->resbutton->setText("Частное");//изменение окна "resultlabel" на "Частное"
    ui->errorlabel->setVisible(false);//обнуление окна "errorlabel"
    ui->resultLabel->setVisible(false);//обнуление окна "errorlabel"
}

void Widget::on_sub_clicked()//ф-ия вычитания
{
    ui->labelOp1->setText("Уменьшаемое");//изменение окна "operand_1" на "Уменьшаемое"
    ui->labelOp2->setText("Вычитаемое");//изменение окна "operand_1" на "Вычитаемое"
    ui->resbutton->setText("Разность");//изменение окна "resultlabel" на "Разность"
    ui->errorlabel->setVisible(false);//обнуление окна "errorlabel"
    ui->resultLabel->setVisible(false);//обнуление окна "errorlabel"
}

void Widget::on_resbutton_clicked()
{
    int op1, op2, res;
    bool ok, ok2;
    QString str;

    if (ui->sum->isChecked())//блок суммы
    {
        str = ui->operand1->text();//ввод текста
        op1 = str.toInt(&ok); //флаг успешности преобразования

        if (ok)
        {
            str = ui->operand2->text();//ввод текста
            op2 = str.toInt(&ok2);//флаг успешности преобразования
            if (ok2)
            {
                res = op1 + op2;
                ui->errorlabel->setVisible(false);//обнуляет окно ошибки
                ui->resultLabel->setNum(res);//вывод результата
                ui->resultLabel->setVisible(true);
            }
            else
            {
                ui->errorlabel->setText("Ошибка во втором слaгаемом");
                ui->errorlabel->setVisible(true);
                ui->resultLabel->setVisible(false);//обнуляет окно ошибки
            }
        }
        else
        {
            ui->errorlabel->setText("Ошибка в первом слагаемом");
            ui->errorlabel->setVisible(true);
            ui->resultLabel->setVisible(false);//обнуляет окно ошибки
        }
    }

    if(ui->div->isChecked())//блок деления
    {
        str = ui->operand1->text();//ввод текста
        op1 = str.toInt(&ok);//флаг успешности преобразования

        if (ok)
        {
            str = ui->operand2->text();//ввод текста
            op2 = str.toInt(&ok2);//флаг успешности преобразования
            if (ok2 && (op2 != 0))
            {
                res = op1 / op2;
                ui->errorlabel->setVisible(false);//обнуляет окно ошибки
                ui->resultLabel->setNum(res);//вывод результата
                ui->resultLabel->setVisible(true);
            }
            else
            {
                ui->errorlabel->setText("Ошибка в делителе");
                ui->errorlabel->setVisible(true);//показыват окно ошибки
                ui->resultLabel->setVisible(false);//обнуляет окно ошибки
            }
        }
        else
        {
            ui->errorlabel->setText("Ошибка в делимом");
            ui->errorlabel->setVisible(true);//показыват окно ошибки
            ui->resultLabel->setVisible(false);//обнуляет окно ошибки
        }
    }

    if(ui->mul->isChecked())//ф-ия деления
    {
        str = ui->operand1->text();//ввод текста
        op1 = str.toInt(&ok);//флаг успешности преобразования

        if (ok)
        {
            str = ui->operand2->text();//ввод текста
            op2 = str.toInt(&ok2);//флаг успешности преобразования
            if (ok2)
            {
                res = op1 * op2;
                ui->errorlabel->setVisible(false);//обнуляет окно ошибки
                ui->resultLabel->setNum(res);//вывод результата
                ui->resultLabel->setVisible(true);
            }
            else
            {
                ui->errorlabel->setText("Ошибка во втором множителе");
                ui->errorlabel->setVisible(true);//показыват окно ошибки
                ui->resultLabel->setVisible(false);//обнуляет окно ошибки
            }
        }
        else
        {
            ui->errorlabel->setText("Ошибка в первом множителе");
            ui->errorlabel->setVisible(true);//показыват окно ошибки
            ui->resultLabel->setVisible(false);//обнуляет окно ошибки
        }
    }

    if(ui->sub->isChecked())//ф-ия вычитания
    {
        str = ui->operand1->text();//ввод текста
        op1 = str.toInt(&ok);//флаг успешности преобразования

        if (ok)
        {
            str = ui->operand2->text();//ввод текста
            op2 = str.toInt(&ok2);//флаг успешности преобразования
            if (ok2)
            {
                res = op1 - op2;
                ui->errorlabel->setVisible(false);//обнуляет окно ошибки
                ui->resultLabel->setNum(res);//вывод результата
                ui->resultLabel->setVisible(true);
            }
            else
            {
                ui->errorlabel->setText("Ошибка ввычитаемом");
                ui->errorlabel->setVisible(true);//показыват окно ошибки
                ui->resultLabel->setVisible(false);//обнуляет окно ошибки
            }
        }
        else
        {
            ui->errorlabel->setText("Ошибка в уменьшаемом");
            ui->errorlabel->setVisible(true);//показыват окно ошибки
            ui->resultLabel->setVisible(false);//обнуляет окно ошибки
        }
    }

}
