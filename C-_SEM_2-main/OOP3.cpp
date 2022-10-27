#include <iostream>

using namespace std;

/*
			Картинка наследования
					A1
					|
					|
					|
				     ___B1___
				    /	     \
			           /	      \
			          /	       \
			         C1  	  	C2
			  
Необходимо реализовать указанную схему наследования. В схеме «0» А1 –родитель для классов B1, B2.
	1 Каждый класс содержит защищённую переменную. 
Например: A1содержит переменную a1, B1 – b1, C2 – c2 и т.п. Каждый класс имеетконструктор, присваивающий этой переменной некое значение.
Конструкторы производных классов должны вызывать конструкторы базовых классов и передавать туда параметры.
	2 В базовых классах реализовать функцию print(), которая выводит на консоль имя класса, из которого она вызвана. В производных классах
переопределять её, чтобы она выводила корректный результат.

Например:
A1 a;
a.print(); => “A1”
B1 b;
b.print(); => “B1”

	3 Написать функцию show(), которая выводит все доступные для этого класса переменные. Например, в классе B1 доступны локальные
переменные класса B1 и некоторые переменные из родительского класса A1. 

Переопределить её в производных классах.
A1 a;
a.show(); => только переменные в A1
B1 b;
b.show(); => переменные из B1 и A1

*/



class A1
{
protected:
	int a1 = 0;
public:
	A1(int val = 0) : a1(val) {};
	virtual void print() { cout << "\n \t -> А1\n"; }
	virtual void show() { cout << "\nA1 = " << a1 << '\t'<< endl; }
};

class B1 : virtual public A1
{
protected:
	int b1 = 0;
public:
	B1(int val, int val_2) : b1(val), A1(val_2) {};
	void print() { cout << "\n\t ->B1\n"; }
	void show() { cout << "\nA1 = " << a1 << "\tB1 = " << b1 << endl;  }
};

class C1 : public B1
{
protected:
	int c1 = 0;
public:
	C1(int val, int val_2, int val_3) :c1(val), B1(val_2, val_3), A1(val_3) {}; //наследуем 2 конструктора ,т.к. внуку далеко идти до бабушки
	void print() { cout << "\n\t ->C1\n"; }
	void show() { cout << "\nA1 = " << a1 << "\tB1 = " << b1 << "\tC1 = " << c1<< endl; }
};

class C2 : public B1
{
protected:
	int c2 = 0;
public:
	C2(int val, int val_2, int val_3) :c2(val), B1(val_2, val_3), A1(val_3) {};
	void print() { cout << "\n\t ->C2\n"; }
	void show() { cout << "\nA1 = " << a1 << "\tB1 = " << b1 << "\tC2 = " << c2 << endl; }
};

int main()
{
	setlocale(LC_ALL, "Ru-ru");

	B1 b1(5,4);
	b1.print();
	b1.show();

	A1* a1 = &b1;
	a1->print();
	a1->show();

	C1 c1(3, 4, 5);
	c1.print();
	c1.show();

	B1* b2 = &c1;
	b2->print();
	b2->show();


	return 0;
}
