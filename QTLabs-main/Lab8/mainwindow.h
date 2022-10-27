#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox> // библиотека с окошками сообщений

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ButtonRow_clicked();

    void on_spinBoxRow_valueChanged(int arg1);

    void on_tableWidget_cellChanged(int row, int column);

    void on_ButtonDeleteRow_clicked();

    void on_ButtonRes_clicked();

private:
    Ui::MainWindow *ui;
    void Ploshad_Gaussa(int x[],int i,int y[]);
};
#endif // MAINWINDOW_H
