#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <math.h>
#include <cmath>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_mul_clicked();

    void on_sum_clicked();

    void on_div_clicked();

    void on_sub_clicked();

    void on_resbutton_clicked();

    void on_sqrt_clicked();


private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
