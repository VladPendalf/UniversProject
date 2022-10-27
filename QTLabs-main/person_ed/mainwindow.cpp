#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButton_clear->click();// очищает значения
    ui->lineEdit_Points->setReadOnly(true);//запрещает менять текст
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clear_clicked()
{
    {   //очищаем места вывода результатов и класса
        ui->label_hp_value->clear();
        ui->label_mp_value->clear();
        ui->label_atk_value->clear();
        ui->label_def_value->clear();
        ui->label_class_value->clear();
    }
    {   //очищаем ввод результатов и класса
        ui->lineEdit_Points->setText("20");
        ui->lineEdit_dex->setText("0");
        ui->lineEdit_int->setText("0");
        ui->lineEdit_luck->setText("0");
        ui->lineEdit_str->setText("0");
        ui->radioButton_Sex_M->setAutoExclusive(false);
        ui->radioButton_Sex_M->setChecked(false);
        ui->radioButton_Sex_W->setAutoExclusive(false);
        ui->radioButton_Sex_W->setChecked(false);

    }
    ui->lineEdit_str->setVisible(true);
    points = 20;//максимум очков
    ui->lineEdit_Points->setText(QString::number(points));//преобразуем число в текст и записываем его в lineEdit
}

void MainWindow::on_pushButton_create_clicked()
{
    QString name;//имя
    int leng;//длина имени
    bool flag;//признак успешности генерации
    int str,dex,intel,luck;//параметры

    name.clear();
    name = ui->lineEdit_Name->text();
    leng = name.length();
    if ((leng < 3) ||(leng >20))
    {
        flag = false;
        QMessageBox::warning(this, "Ошибка", "Длина имени должа быть от 3 до 20 симоволов.");
    }
    else
    {
        flag = true;
    }
    if (flag)
    {
        if ((!ui->radioButton_Sex_M->isChecked())&&(!ui->radioButton_Sex_W->isChecked()))
        {
            flag = false;
            QMessageBox::warning(this, "Ошибка", "Пол не выбран.");
        }
        else
        {
            flag = true;
        }
    }
    if (flag) //сила
    {
        str = ui->lineEdit_str->text().toInt(&flag);
        if (!flag)
        {
            QMessageBox::warning(this, "Ошибка", "Не верное значение параметра Сила.");
        }
        else
        {
            if ((str <1)|| (str > 10))
            {
                flag = false;
                QMessageBox::warning(this, "Ошибка", "Cила должна быть от 1 до 10 включительно.");
            }
        }
    }
    //Самим релизнуть
    if (flag) //ловкость
    {
        dex = ui->lineEdit_dex->text().toInt(&flag);
        if (!flag)
        {
            QMessageBox::warning(this, "Ошибка", "Не верное значение параметра Ловкость.");
        }
        else
        {
            if ((dex <1)|| (dex > 10))
            {
                flag = false;
                QMessageBox::warning(this, "Ошибка", "Ловкость должна быть от 1 до 10 включительно.");
            }
        }
    }
    if (flag) //интеллект
    {
        intel = ui->lineEdit_int->text().toInt(&flag);
        if (!flag)
        {
            QMessageBox::warning(this, "Ошибка", "Не верное значение параметра Интеллект.");
        }
        else
        {
            if ((intel <1)|| (intel > 10))
            {
                flag = false;
                QMessageBox::warning(this, "Ошибка", "Интеллект должна быть от 1 до 10 включительно.");
            }
        }
    }
    if (flag) //удача
    {
        luck = ui->lineEdit_luck->text().toInt(&flag);
        if (!flag)
        {
            QMessageBox::warning(this, "Ошибка", "Не верное значение параметра Удача.");
        }
        else
        {
            if ((dex <1)|| (dex > 10))
            {
                flag = false;
                QMessageBox::warning(this, "Ошибка", "Удача должна быть от 1 до 10 включительно.");
            }
        }
    }

    if (flag)// проверка суммы очков
    {
        int sum= points - (str+dex+intel+luck);
        ui->lineEdit_Points->setText(QString::number(sum));
        if (sum!=0)
        {
            flag = false;//false
            if (sum > 0)
            {
                QMessageBox::warning(this, "Ошибка", "Нужно потратить все очки.");
            }
            else
            {
                QMessageBox::warning(this, "Ошибка", "Нельзя больше чем "+QString::number(points)+" очков." );
            }
        }
    }

    if (flag)// вывод результата
    {
        int hp,mp,atk,def;
        hp = 8*str+2*dex;
        mp = 8*intel+dex+luck;
        atk = 6*str+2*dex+2*luck;
        def = 7*dex+3*luck;

        class_person(hp,mp,atk,def);

        ui->label_hp_value->setNum(hp);
        ui->label_mp_value->setNum(mp);
        ui->label_atk_value->setNum(atk);
        ui->label_def_value->setNum(def);
    }
    else
    {
        ui->label_hp_value->clear();
        ui->label_mp_value->clear();
        ui->label_atk_value->clear();
        ui->label_def_value->clear();
        ui->label_class_value->clear();
    }
}

void MainWindow::on_pushButton_rand_clicked()
{
    QString name;//имя
    int leng;//длина имени
    bool flag, random;
    random = false;
    ui->lineEdit_Points->setText("20");
    int str,dex,intel,luck;//параметры
    str = 0; dex = 0; intel = 0; luck = 0;
    srand(time(NULL));

    name.clear();
    name = ui->lineEdit_Name->text();
    leng = name.length();
    if ((leng < 3) ||(leng >20))
    {
        flag = false;
        QMessageBox::warning(this, "Ошибка", "Длина имени должа быть от 3 до 20 симоволов.");
    }
    else
    {
        flag = true;
        while (!random)
        {
            if (((str + dex + intel + luck) > points) || ((str + dex + intel + luck) < points))
            {
                str = rand() % 9 + 2;
                dex = rand() % 9 + 2;
                intel = rand() % 9 + 2;
                luck = rand() % 9 + 2;
                random = false;
            }
            else
            {
                random = true;
                ui->lineEdit_str->setText(QString::number(str));
                ui->lineEdit_dex->setText(QString::number(dex));
                ui->lineEdit_int->setText(QString::number(intel));
                ui->lineEdit_luck->setText(QString::number(luck));
            }
        }


        ui->radioButton_Sex_M->setChecked(false);
        ui->radioButton_Sex_W->setChecked(false);

        if (random)
        {
            flag = rand() % 2;
            if (flag == 0)
                ui->radioButton_Sex_M->click();
            else
                ui->radioButton_Sex_W->click();
        }

        if (random)// вывод результата
        {
            int hp,mp,atk,def;
            hp = 8*str+2*dex;
            mp = 8*intel+dex+luck;
            atk = 6*str+2*dex+2*luck;
            def = 7*dex+3*luck;

            class_person(hp,mp,atk,def);

            ui->label_hp_value->setNum(hp);
            ui->label_mp_value->setNum(mp);
            ui->label_atk_value->setNum(atk);
            ui->label_def_value->setNum(def);
        }
        else
        {
            ui->label_hp_value->clear();
            ui->label_mp_value->clear();
            ui->label_atk_value->clear();
            ui->label_def_value->clear();
            ui->label_class_value->clear();
        }
    }
}

void MainWindow::class_person(int hp,int mp, int atk,int def) // class_person(hp,mp,atk,def);
{
    if (ui->radioButton_Sex_M->isChecked())
    {
        if (hp >= 50 && mp >= 50)
        {
            ui->label_class_value->setText("Паладин");
        }
        if (hp >= 50 && def > atk )
        {
            ui->label_class_value->setText("Воин");
        }
        if (mp >= 50 && atk > def)
        {
            ui->label_class_value->setText("Колдун");
        }
        if (mp >= 50 && def > atk)
        {
            ui->label_class_value->setText("Жрец");
        }
        if (hp >= 50 && atk > def)
        {
            ui->label_class_value->setText("Разбойник");
        }
    }
    else
    {
        if (hp >= 50 && mp >= 50)
        {
            ui->label_class_value->setText("Паладиша");
        }
        if (hp >= 50 && def > atk )
        {
            ui->label_class_value->setText("Воительница");
        }
        if (mp >= 50 && atk > def)
        {
            ui->label_class_value->setText("Колдунья");
        }
        if (mp >= 50 && def > atk)
        {
            ui->label_class_value->setText("Жрица");
        }
        if (hp >= 50 && atk > def)
        {
            ui->label_class_value->setText("Разбойница");
        }
    }
}
