#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //ограничения кол-ва строк
    ui->spinRow->setMinimum(1);
    ui->spinRow->setMaximum(1000000);

    //делаем 1 столбик и строку
    ui->mainWidget->setColumnCount(1);
    ui->mainWidget->setRowCount(1);

    //блокируем ввод в lineEdit
    ui->lineEdit_Min->setReadOnly(true);
    ui->lineEdit_Average->setReadOnly(true);
    ui->lineEdit_Max->setReadOnly(true);

    //авто-активация cортировки пузырьком
    ui->bubble->click();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_spinRow_valueChanged(int arg1) //изменяем кол-во строк
{
    ui->mainWidget->setRowCount(arg1);

    warning = false; //выводим предупреждение для monkey_sort
}

//----------------------------------------------------------------------//
// on_pushRandom_clicked() //Кнопка рандома
// on_pushMin_clicked() //Кнопка минимального значения
// on_pushAverage_clicked() //Кнопка среднего значения
// on_pushMax_clicked() //Кнопка максимального значения
// isTableOK() //проверка таблицы
// on_pushSort_clicked() //кнопка сортировка
// on_mainWidget_itemChanged(QTableWidgetItem *item) //проверка + подсветка
// isSorted(double *arr,int size) //проверка отсортированности
// on_pushSearch_clicked() //кнопка поиска
// TableIsSorted() //массив отсортирован
//
//----------------------Type-of-Sort-------------------------
// Bubble_Sort(double *arr, int size)
// Quick_Sort(double *arr, int size)
// Comb_Sort(double *arr, int size)
// Gnome_Sort(double *arr, int size)
// Monkey_Sort(double *arr , int size)
// Bin_Sort(double *arr,double num, int size)
//----------------------------------------------------------------------//

void MainWindow::on_pushRandom_clicked() //Кнопка рандома
{
    warning = false; //выводим предупреждение для monkey_sort

    ui->answer->clear();

    int row = ui->mainWidget->rowCount(); //число строк

    for (int i = 0; i < row; i++)
    {
        if (ui->mainWidget->item(i,0) == nullptr) //Ячейки не существует
        {
            QTableWidgetItem *ti; //объявили указатель
            ti = new QTableWidgetItem; //выделили память под ячейку
            ui->mainWidget->setItem(i,0,ti); //создали ячейку
        }
        ui->mainWidget->item(i,0)->setText(QString::number(rand()%10000-6000)); //случайные числа
        ui->mainWidget->item(i,0)->setBackgroundColor(Qt::white);
    }

    line_arr = false;

    //очищаем окошки вывода
    ui->lineEdit_Min->clear();
    ui->lineEdit_Average->clear();
    ui->lineEdit_Max->clear();
}

//-----------------------------------------------------------------------

void MainWindow::on_pushMin_clicked() //кнопка минимального значения
{
    tableIsOk = isTableOK(); //проверка таблицы

    TableIsSorted();

    double min = __DBL_MAX__;


    if (tableIsOk)
    {
        for (int i = 0; i < ui->mainWidget->rowCount(); ++i) //проверяем все числа
        {
            if (ui->mainWidget->item(i,0)->text().toDouble() < min) //если находим меньше, чем min , то заменяем min
            {
                min = ui->mainWidget->item(i,0)->text().toDouble();
            }
        }

        ui->lineEdit_Min->setText(QString::number(min)); //выводим значением
    }
    else
    {
        QMessageBox::warning(this,"Error","Сначала корректно заполните таблицу!");
    }

}


//-----------------------------------------------------------------------

void MainWindow::on_pushAverage_clicked() //Кнопка среднего значения
{
    tableIsOk = isTableOK(); //проверка таблицы

    if (tableIsOk)
    {
        sum = 0;

        for (int i = 0; i < ui->mainWidget->rowCount(); ++i)
        {
            sum += ui->mainWidget->item(i,0)->text().toDouble(); //складываем все числа
        }

        ui->lineEdit_Average->setText(QString::number(sum / ui->mainWidget->rowCount())); //выводим среднее значение
    }
    else
    {
        QMessageBox::warning(this,"Error","Сначала корректно заполните таблицу!");
    }
}

//-----------------------------------------------------------------------

void MainWindow::on_pushMax_clicked() //Кнопка максимального значения
{
    tableIsOk = isTableOK(); //проверка таблицы

    TableIsSorted();

    double max = __DBL_MIN__;


    if (tableIsOk)
    {
        for (int i = 0; i < ui->mainWidget->rowCount(); ++i) //проверяем все числа
        {
            if (ui->mainWidget->item(i,0)->text().toDouble() > max) //если находим меньше, чем min , то заменяем min
            {
                max = ui->mainWidget->item(i,0)->text().toDouble();
            }
        }

        ui->lineEdit_Max->setText(QString::number(max)); //выводим значением
    }
    else
    {
        QMessageBox::warning(this,"Error","Сначала корректно заполните таблицу!");
    }
}

//-----------------------------------------------------------------------

bool MainWindow::isTableOK() //проверка таблицы
{
    bool fl_gl = true;

    for (int i = 0; i < ui->mainWidget->rowCount(); ++i)
    {
        bool fl_loc;

        if (ui->mainWidget->item(i,0) != nullptr) //если ячейка существует
        {
            ui->mainWidget->item(i,0)->text().toDouble(&fl_loc);  //проверка на корректность числа

            if (!fl_loc) //если число не корректно
            {
                fl_gl = false;
                ui->mainWidget->scrollToItem(ui->mainWidget->item(i,0)); //позиционируем курсор на ячейке
                ui->mainWidget->editItem(ui->mainWidget->item(i,0));
                break;
            }
        }
        else
        {
            ui->mainWidget->scrollToItem(ui->mainWidget->item(i,0)); //позиционируем курсор на ячейке
            ui->mainWidget->editItem(ui->mainWidget->item(i,0));
            fl_gl = false;
            break;
        }
    }

    if (ui->mainWidget->rowCount() + ui->mainWidget->columnCount() == 0) //если как-то сделали значение таблицы 0х0
    {
        fl_gl = false;
    }

    return fl_gl;
}

//-----------------------------------------------------------------------

void MainWindow::on_pushSort_clicked() //кнопка сортировка
{
    no_auto_change = false;

    tableIsOk = isTableOK();
    if (tableIsOk)
    {
        int size = ui->mainWidget->rowCount(),
                k = 0;

        if (size <= 1000000)
        {
            double *arr;
            int size = ui->mainWidget->rowCount();

            arr = new double[size];

            bool fl_gl = true,
                    fl_loc = true;

            for (int i = 0; i < ui->mainWidget->rowCount(); i++)
            {
                if (ui->mainWidget->item(i,0) != nullptr)
                {
                    ui->mainWidget->item(i,0)->text().toDouble(&fl_loc);

                    if (fl_loc)
                    {
                        arr[k] = ui->mainWidget->item(i,0)->text().toDouble();
                        k++;
                    }
                    else
                    {
                        fl_gl = false;

                        ui->mainWidget->item(i,0)->setBackgroundColor(Qt::red);
                    }
                }
                else
                {
                    QTableWidgetItem *ti;
                    ti = new QTableWidgetItem;
                    ui->mainWidget->setItem(i,0,ti);
                    fl_gl = false;
                    fl_loc = false;
                }
            }


            //---------------------------------------------------//
            for (int i = 1; i < size; i++)                       //
            {                                                    //
                if (arr[i-1] > arr[i])                           //
                {                                                //
                    line_arr = false;                            //
                    break;                                       //  // линейность массива
                }                                                //
                else                                             //
                {                                                //
                    line_arr = true;                             //
                }                                                //
            }                                                    //
            //---------------------------------------------------//


            if (fl_gl && fl_loc)
            {
                if (ui->bubble->isChecked()) //пузырьком
                {
                    if (size > 10000)
                    {
                        if (!warning)
                        {
                            QMessageBox::warning(this,"Error","Слишком много элементов. Будет сбой программы. \nСтабильная работа при 10000 элементах.\nНажмите еще раз сортировать, чтоб выполнить \nсортировку большего числа элементов.");
                            warning = true;
                        }
                        else
                        {
                            Bubble_Sort(arr,size);
                            warning = true; //выключаем предупреждение для bogosort
                        }
                    }
                    else
                    {
                        Bubble_Sort(arr,size); //обезьянья
                    }
                }
                else if (ui->Quick->isChecked()) //быстрая
                {
                    Quick_Sort(arr,size);
                }
                else if (ui->Comb->isChecked()) //расческа
                {
                    Comb_Sort(arr,size);
                }
                else if (ui->Gnome->isChecked()) //гномья
                {
                    if (size > 10000)
                    {
                        if (!warning)
                        {
                            QMessageBox::warning(this,"Error","Слишком много элементов. Будет сбой программы. \nСтабильная работа при 10000 элементах.\nНажмите еще раз сортировать, чтоб выполнить \nсортировку большего числа элементов.");
                            warning = true;
                        }
                        else
                        {
                            Gnome_Sort(arr,size);
                            warning = true; //выключаем предупреждение для bogosort
                        }
                    }
                    else
                    {
                        Gnome_Sort(arr,size); //обезьянья
                    }
                }
                else //Обезьянья
                {
                    if (size > 9)
                    {
                        if (!warning)
                        {
                            QMessageBox::warning(this,"Error","Слишком много элементов. Будет сбой программы. \nСтабильная работа при 9 элементах.\nНажмите еще раз сортировать, чтоб выполнить \nсортировку большего числа элементов.");
                            warning = true;
                        }
                        else
                        {
                            Monkey_Sort(arr,size);
                            warning = true; //выключаем предупреждение для bogosort
                        }
                    }
                    else
                    {
                        Monkey_Sort(arr,size); //обезьянья
                    }
                }
            }
            else
            {
                QMessageBox::warning(this,"Error","Сначала корректно заполните таблицу!");
            }
            no_auto_change = true;

            delete [] arr;
            arr = nullptr;
        }
    }
    else
    {
        QMessageBox::warning(this,"Error","Сначала корректно заполните таблицу!");
    }
}

//-----------------------------------------------------------------------

void MainWindow::on_mainWidget_itemChanged(QTableWidgetItem *item) //проверка + подсветка
{
    if (item != nullptr) //ячейка существует
    {
        bool ok;

        item->text().toDouble(&ok);

        if (!ok) //число не преобразовалось
        {
            item->setBackground(Qt::red);

            lock = true;
        }
        else
        {
            lock = false;

            if (!isSortingNow)
            {
                item->setBackground(Qt::white);
            }
        }
    }
}

//-----------------------------------------------------------------------

bool MainWindow::isSorted(double *arr,int size) //проверка отсортированности
{
    while (--size > 0)
    {
        if (arr[size - 1] > arr[size])
        {
            return false;
        }
    }
    return true;
}

//-----------------------------------------------------------------------

void MainWindow::TableIsSorted()
{
    double *arr;

    int size = ui->mainWidget->rowCount();

    arr = new double[size];

    bool fl_loc = true;

    for (int i = 0, k = 0; i < ui->mainWidget->rowCount(); i++)
    {
        if (ui->mainWidget->item(i,0) != nullptr)
        {
            ui->mainWidget->item(i,0)->text().toDouble(&fl_loc);

            if (fl_loc)
            {
                arr[k] = ui->mainWidget->item(i,0)->text().toDouble();
                k++;
            }
            else
            {
                ui->mainWidget->item(i,0)->setBackgroundColor(Qt::red);
            }
        }
        else
        {
            QTableWidgetItem *ti;
            ti = new QTableWidgetItem;
            ui->mainWidget->setItem(i,0,ti);
        }
    }

    //---------------------------------------------------//
    for (int i = 1; i < size; i++)                       //
    {                                                    //
        if (arr[i-1] > arr[i])                           //
        {                                                //
            line_arr = false;                            //
            break;                                       //  // линейность массива
        }                                                //
        else                                             //
        {                                                //
            line_arr = true;                             //
        }                                                //
    }                                                    //
    //---------------------------------------------------//
}
//-------------!!!----------Функции-Сортировок-------------!!!-----------

//--------------------------Сортировка-Пузырьком-------------------------

void MainWindow::Bubble_Sort(double *arr, int size)
{
    bool exit = false;

    while(!exit)
    {
        exit = true;
        for (int i = 0; i < size - 1; i++)
        {
            if (arr[i] > arr[i + 1])
            {
                std::swap(arr[i],arr[i+1]);
                exit = false;
            }
        }
    }

    line_arr = true;

    //------------------------------------------------------------------//
    int k = 0;                                                          //
    //
    for (int i = 0; i < ui->mainWidget->rowCount(); i++)                //
    {                                                                   //
        if (ui->mainWidget->item(i,0) == nullptr) //если ячейки нет     //
        {                                                               //
            QTableWidgetItem *ti;                                       //
            ti = new QTableWidgetItem;                                  //
            ui->mainWidget->setItem(i,0,ti);                            //  //выводим массив
        }                                                               //
        else                                                            //
        {                                                               //
            ui->mainWidget->item(i,0)->setText(QString::number(arr[k]));//
            ui->mainWidget->item(i,0)->setBackgroundColor(Qt::white);   //
            k++;                                                        //
        }                                                               //
    }                                                                   //
    //------------------------------------------------------------------//
}

//--------------------------Быстрая-Сортировка----------------------------

//--------Вспомогательная-функция-Quick_Sort------------------------------

void Quick_Sort_Dependency(double *arr, int size)
{
    //------------------//
    int i = 0,          // //Указатели на начало и конец массива
            j = size - 1;   //
    //------------------//

    //-----------------------//
    double mid = arr[size/2];// //Центральный элемент
    //-----------------------//

    //-------------Делим-массив-----------
    do
    {
        while(arr[i] < mid)
        {
            i++;
        }

        while (arr[j] > mid)
        {
            j--;
        }

        if (i <= j)
        {
            std::swap(arr[i],arr[j]);

            i++;
            j--;
        }
    } while (i <= j);
    //------------------------------------


    //--------Рекурсивные-вызовы---------
    if (j > 0)
    {
        Quick_Sort_Dependency(arr,j+1);
    }
    if (i < size)
    {
        Quick_Sort_Dependency(&arr[i], size-i);
    }
    //-----------------------------------

}

//---------Функция-Быстрой-Сортировки------------------------

void MainWindow::Quick_Sort(double *arr, int size)
{
    for (int i = 0; i < ui->mainWidget->rowCount();i++)
    {
        arr[i] = ui->mainWidget->item(i,0)->text().toDouble();
    }

    Quick_Sort_Dependency(arr,size);

    for (int i = 0, k = 0; i < ui->mainWidget->rowCount(); i++)
    {
        ui->mainWidget->item(i,0)->setText(QString::number(arr[k++]));
    }

    line_arr = true;
}

//------------------------------------------------------------------------

//---------------------------Сортировка-Расческой---------------------------

void MainWindow::Comb_Sort(double *arr, int size)
{
    for (int i = 0; i < ui->mainWidget->rowCount(); i++)
    {
        arr[i] = ui->mainWidget->item(i,0)->text().toDouble();
    }

    double index = 1.2343309; // некий коэффициент
    double step = size - 1; //шаг сортировки

    while (step >= 1)
    {
        for (int i = 0; i + step < size ; i++)
        {
            if (arr[i] > arr[int(i + step)])
            {
                std::swap(arr[i],arr[int(i + step)]);
            }
        }
        step /= index;
    }

    for (int i = 0, k = 0; i < ui->mainWidget->rowCount(); i++)
    {
        ui->mainWidget->item(i,0)->setText(QString::number(arr[k++]));
    }

    line_arr = true;
}

//------------------------------------------------------------------------

//---------------------------Гномья-Сортировка----------------------------

void MainWindow::Gnome_Sort(double *arr, int size)
{
    for (int i = 0; i < ui->mainWidget->rowCount(); i++)
    {
        arr[i] = ui->mainWidget->item(i,0)->text().toDouble();
    }

    int index = 0;

    while (index < size)
    {
        if (index == 0)
        {
            index++;
        }
        if (arr[index] >= arr[index-1])
        {
            index++;
        }
        else
        {
            std::swap(arr[index],arr[index - 1]);
            index--;
        }
    }

    for (int i = 0, k = 0; i < ui->mainWidget->rowCount(); ++i)
    {
        ui->mainWidget->item(i,0)->setText(QString::number(arr[k++]));
    }

    line_arr = true;
}

//--------------------------------------------------------------------------

//---------------------------Обезьянья-Сортировка----------------------------

void MainWindow::Shuffle(double *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        std::swap(arr[i],arr[rand()%size]);
    }
}

void MainWindow::Monkey_Sort(double *arr , int size)
{
    isSorted(arr,size);
    while(!isSorted(arr,size))
    {
        Shuffle(arr,size);
    }

    //------------------------------------------------------------------//
    int k = 0;                                                          //
    //
    for (int i = 0; i < ui->mainWidget->rowCount(); i++)                //
    {                                                                   //
        if (ui->mainWidget->item(i,0) == nullptr) //если ячейки нет     //
        {                                                               //
            QTableWidgetItem *ti;                                       //
            ti = new QTableWidgetItem;                                  //
            ui->mainWidget->setItem(i,0,ti);                            //  //выводим массив
        }                                                               //
        else                                                            //
        {                                                               //
            ui->mainWidget->item(i,0)->setText(QString::number(arr[k]));//
            ui->mainWidget->item(i,0)->setBackgroundColor(Qt::white);   //
            k++;                                                        //
        }                                                               //
    }                                                                   //
    //------------------------------------------------------------------//
}

//--------------------------------------------------------------------------

//---------------------------Бинарная-Сортировка----------------------------

void MainWindow::Bin_Sort(double *arr, double num, int size)
{
    double res = -1,
            left = 0,
            right = size;

    QString str = "Номера ячеек:";

    str.append(" ");

    //--------------------------------------

    while (left <= right)
    {
        int mid = abs((right+left) / 2);

        if (num == arr[mid])
        {
            res = num;
            break;
        }
        else if (num < arr[mid])
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    //--------------------------------------

    if (res == -1)
    {

    }
    else
    {
        int count = 0;

        for(int i = 0; i < size; i++)
        {
            if (res == arr[i])
            {
                str.append(QString::number(i+1)+";\n");
                count += 1;
            }
        }
        str.append("\nВаше число встречалось -> " + QString::number(count));
        ui->answer->setText(str);
    }

    //--------------------------------------
}

//--------------------------------------------------------------------------

void MainWindow::on_pushSearch_clicked() //кнопка поиска
{
    double *arr;

    int arr_size = ui->mainWidget->rowCount();

    arr = new double[arr_size];

    bool fl_loc = true,
            fl_gl = true;

    int size = 0;

    tableIsOk = isTableOK(); //проверка таблицы

    //--------------------------------------
    if (tableIsOk)
    {
        if (ui->mainWidget->rowCount() <= 1000000)
        {
            if (fl_loc)
            {
                size = ui->mainWidget->rowCount();

                for (int i = 0, k = 0; i < size; i++)
                {
                    if (ui->mainWidget->item(i,0) != nullptr)
                    {
                        ui->mainWidget->item(i,0)->text().toDouble(&fl_loc);
                        if (fl_loc)
                        {
                            arr[k] = ui->mainWidget->item(i,0)->text().toDouble();
                            k++;
                        }
                        else
                        {
                            fl_gl = false;
                            fl_loc = false;
                            ui->mainWidget->item(i,0)->setBackground(Qt::red);
                        }
                    }
                    else
                    {
                        QTableWidgetItem *ti;
                        ti = new QTableWidgetItem;
                        ui->mainWidget->setItem(i,0,ti);
                        fl_loc = false;
                        fl_gl = false;
                    }
                }
            }

            //--------------------------------------

            if (fl_loc & fl_gl)
            {
                double count = 0;

                bool fl;

                QString str = "Номера ячеек:";

                str.append(" ");

                fl = ui->lineEdit_Search->text().toDouble(&fl);

                if (fl)
                {
                    if (line_arr)//если массив упорядочен
                    {
                        Bin_Sort(arr, ui->lineEdit_Search->text().toDouble(), size); //бинарный поиск
                    }
                    else
                    {
                        for (int i = 0; i < size; i++)
                        {
                            if (arr[i] == ui->lineEdit_Search->text().toDouble())
                            {
                                str.append(QString::number(i+1) + ";\n");
                                count++;
                            }
                        }

                        if (count != 0)
                        {
                            ui->answer->setText(str + "\nВаше число встречалось -> " + QString::number(count));
                        }
                        else
                        {
                            ui->answer->setText("Такого числа нет в таблице!");
                        }
                    }
                }
                else
                {
                    QMessageBox::warning(this,"Error","Сначала корректно заполните строчку!");
                    ui->answer->clear();
                }
            }
        }
        else
        {
            QMessageBox::warning(this,"Error","Сначала корректно заполните таблицу!");
        }
    }
    else
    {
        QMessageBox::warning(this,"Error","Сначала корректно заполните таблицу!");
    }

    //--------------------------------------

    delete [] arr;
    arr = nullptr;
}

//-------------------------------------------------------------------------------------------------------

void MainWindow::on_pushDelete_clicked()
{
    TableIsSorted();

    tableIsOk = isTableOK();

    int i = 0,
        j = 1,
        k = 0;

    double *arr, *ready_arr;

    double max;

    arr = new double[ui->mainWidget->rowCount()];
    ready_arr = new double[ui->mainWidget->rowCount()];

    for (int i = 0; i < ui->mainWidget->rowCount(); i++)
    {
        if (ui->mainWidget->item(i,0) != nullptr)
        {
            arr[i] = ui->mainWidget->item(i,0)->text().toDouble();
        }
        else
        {
            QTableWidgetItem *ti;
            ti = new QTableWidgetItem;
            ui->mainWidget->setItem(i,0,ti);
        }
    }

    for (int i = 0; i < ui->mainWidget->rowCount() - 1; i++)
    {
        max = ui->mainWidget->item(i,0)->text().toDouble();

        if (max < ui->mainWidget->item(i+1,0)->text().toDouble())
        {
            max = ui->mainWidget->item(i+1,0)->text().toDouble();
        }
    }



    if (line_arr)
    {
        if (tableIsOk)
        {
            while (ready_arr[k] != max)
            {
                if (arr[i] == arr[j])
                {
                    while (arr[i] == arr[j])
                    {
                        ready_arr[k] = arr[i];
                        j++;
                    }
                    k++;
                }
                else
                {
                    ready_arr[k] = arr[j];
                    i = j;
                }
            }

            delete [] arr;

            arr = new double[k+1];

            for (int i = 0; i < k; i++)
            {
                arr[i] = ready_arr[i];
            }

            for (int i = 0 ; i < k; i++)
            {
                if (ui->mainWidget->item(i,0) != nullptr)
                {
                   ui->mainWidget->item(i,0)->setText(QString::number(arr[i]));
                }
                else
                {
                    QTableWidgetItem *ti;
                    ti = new QTableWidgetItem;
                    ui->mainWidget->setItem(i,0,ti);
                }
            }

        }

        else
        {

        }
    }
    else
    {
        if (tableIsOk)
        {

        }
        else
        {

        }
    }

    delete [] arr;
    arr = nullptr;

    delete [] ready_arr;
    ready_arr = nullptr;
}
