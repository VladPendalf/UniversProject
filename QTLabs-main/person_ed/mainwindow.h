#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox> // библиотека с окошками сообщений
#include <ctime>
#include <time.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clear_clicked();

    void on_pushButton_create_clicked();

    void on_pushButton_rand_clicked();

private:
    Ui::MainWindow *ui;
    int points;// для максимума очков
    void class_person(int,int,int,int);
};

#endif // MAINWINDOW_H
