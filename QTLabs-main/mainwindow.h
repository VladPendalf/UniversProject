#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidgetItem>
#include <QMessageBox>

#include <algorithm>
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinRow_valueChanged(int arg1);

    void on_pushRandom_clicked();

    void on_pushMin_clicked();

    void on_pushAverage_clicked();

    void on_pushMax_clicked();

    void on_pushSort_clicked();

    void on_mainWidget_itemChanged(QTableWidgetItem *item);

    void on_pushSearch_clicked();

    void on_pushDelete_clicked();

    void TableIsSorted();

private:
    Ui::MainWindow *ui;

    bool isSortingNow=false;

    bool tableIsOk = true;
    bool isTableOK();

    bool no_auto_change;

    double sum = 0;

    int numOfElements = 0;

    int minRand = 0;
    int maxRand = 200;

    bool warning = false;

    bool lock = false;
    bool line_arr = false;

    std::vector<double> arr; //используется в удалении

    //Cортировки
    void Bubble_Sort(double *arr, int size); //пузырьком
    void Quick_Sort(double *arr, int size); //быстрая
    void Comb_Sort(double *arr, int size); //расческа
    void Gnome_Sort(double *arr, int size); //гномья
    void Monkey_Sort(double *arr,int size); //обезьянья

    void Bin_Sort(double *arr, double num, int size);

    void Shuffle(double *arr, int size);
    bool isSorted(double *arr, int size);

    QPalette defPal = QPalette();
    QPalette redPal;
};
#endif // MAINWINDOW_H
