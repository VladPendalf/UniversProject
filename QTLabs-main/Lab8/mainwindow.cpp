#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBoxRow->setValue(1);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_spinBoxRow_valueChanged(int arg1) //устанавливаем кол-во строк
{
    if (arg1 > 0) //если строк больше 0
        ui->tableWidget->setRowCount(arg1);
    else
    {
        QMessageBox::warning(this, "Ошибка", "Не трогай то, что работает.");
        ui->spinBoxRow->setValue(1);
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount());
    }
}

void MainWindow::on_ButtonRow_clicked() //Добавляем строки
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
    ui->spinBoxRow->setValue(ui->tableWidget->rowCount());
}



void MainWindow::on_tableWidget_cellChanged(int row, int column) //проверка данных
{
    bool fl;
    ui->tableWidget->item(row,column)->text().toUInt(&fl);
    if(!fl){
        ui->tableWidget->item(row,column)->setBackground(Qt::red); //если фигню ввел
    } else {
        ui->tableWidget->item(row,column)->setBackground(Qt::white); //если не фигню
    }
}

void MainWindow::on_ButtonDeleteRow_clicked() //Удаляем строки
{
    ui->tableWidget->setRowCount(ui->tableWidget->rowCount()-1);
    ui->spinBoxRow->setValue(ui->tableWidget->rowCount());
}

void MainWindow::on_ButtonRes_clicked()
{
    /*
        взять все значения с таблицы
        создать динамический массив, для их хранения
            //считываение слева на право
        найти формулу площади и периметра фигур через координаты вершин (какую-то универсальную формулу мать ее за ногу, блять...)
        сделать расчет !не накосячить в матане (будет грустно) {формула площади Гаусса}
        вывести в Окоше Площадь и Периметр
    */
    int row_count = ui->tableWidget->rowCount();
    int col_count = ui->tableWidget->columnCount();
    int P = 0;

    //создание динамического массива под результат координат
    int* x = new int[row_count];
    int* y = new int[row_count];
    for (int i = 0; i < row_count; i++)
    {
        x[i] = 0; // иксы
        y[i] = 0; // игрики
    }

    bool fl;

    //начинаем работать с данными в массиве
    for (int i=0;i<row_count;i++) //строки
    {
        for (int j=0;j<col_count;j+=2) //cтолбцы
        {
            if (ui->tableWidget->item(i,j) != nullptr)
            {
                x[i] = ui->tableWidget->item(i,j)->text().toInt(&fl);
                y[i] = ui->tableWidget->item(i,j+1)->text().toInt(&fl);
                if (i > 1)
                {
                    P +=sqrt(pow(x[i]-x[i-1],2)+pow(y[i]-y[i-1],2));
                }
            }
            else
                fl = false;
        }
    }

    Ploshad_Gaussa(x, row_count, y);
    ui->Perimetr->setText(QString::number(P));

    //Удаление двумерного массива
    for (int i = 0; i < row_count;i++)
    {
        x[i]=NULL;
        y[i] = NULL;
    }
    delete[] x;
    delete[] y;
    y = nullptr;
    x = nullptr;
}

void MainWindow::Ploshad_Gaussa(int x[], int i, int y[])
{
    int S = 0, pr1 = 0,pr2 = 0;
    for (int j = 0; j < i-1; j++)
    {
        pr1 += x[j]*y[j+1];
        pr2 += x[j+1]*y[j];
    }
    S = 0.5 * abs(pr1 +x[i]*y[1] - pr2 - x[1]*y[i]) ;
    ui->Ploshad->setText(QString::number(S));
}
