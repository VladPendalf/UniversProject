#include <iostream>
#include <algorithm>


using namespace std;


//-------------------------ТЗ-------------------------------------------|
//Класс Дробь - Сложение с целым числом , вычитание целого числа (1.1)  |
//Класс Наследник от Дробь - Сложение целого числа и дроби (1.2)		|
//----------------------------------------------------------------------|




class Fraction
{
protected:
	int denominator; //знаменатель
	int numerator; //числитель
public:
	//Конструкторы
	Fraction() :numerator(1), denominator(1) {  }; //по умолчанию

	Fraction(const Fraction& fraction) :numerator(fraction.numerator), denominator(fraction.denominator) {  }; //копирования

	Fraction(const int& val_1,const int& val_2) :numerator(val_1), denominator(val_2) {  };//обычный

	~Fraction() {  }//деструктор

	//Функционал
	void show(); //вывод дроби
	
	int get_den(); //геттер
	
	int get_num();//геттер

	void set_num(const int& num); //сеттер

	void set_den(const int& num); //сеттер

	Fraction operator=(const Fraction& val);

	Fraction operator+(const int& num);//сложение с целым числом

	Fraction operator-(const int& num);//сложение с целым числом
};

Fraction Fraction::operator=(const Fraction& val)
{
	if (this == &val)
	{
		return *this;
	}

	numerator = val.numerator;
	denominator = val.denominator;
}

class Fraction_v2 : public Fraction //наследник
{
public:
		Fraction_v2(const int& val_1, const int& val_2)
		{
			numerator = val_1;
			denominator = val_2;
			 
		};
		Fraction_v2()  
		{
			numerator = 1;
			denominator = 1;
		};
		Fraction_v2(const Fraction_v2& fraction) {

			numerator = fraction.numerator;
			denominator = fraction.denominator;
		}
		
		Fraction_v2(Fraction& fraction)
		{
			denominator = fraction.get_den();
			numerator = fraction.get_num();
		}

		Fraction_v2 operator=(Fraction x)
		{
			if (this == &x)
			{
				return *this;
			}

			numerator = x.get_num();
			denominator = x.get_den();

		}
		Fraction_v2 operator=(const Fraction_v2& hz)
		{
			if (this == &hz)
			{
				return *this;
			}

			numerator = hz.numerator;
			denominator = hz.denominator;
		}


		~Fraction_v2() {}

		friend Fraction_v2 operator+(int num, Fraction val);
};

Fraction_v2 operator+(int num, Fraction val)
{
	Fraction_v2 temp;
	temp.numerator = val.get_num() + num*val.get_den();
	temp.denominator = val.get_den();
	return temp;
}

void Fraction::set_den(const int& num)
{
	denominator = num;
}

void Fraction::set_num(const int& num)
{
	numerator = num;
}

void Fraction::show() //вывод дроби
{

	if (denominator == 1)
	{
		cout << "Числитель = " << numerator << endl;
	}
	else
	{
		cout << "Числитель = " << numerator << "\nЗнаменатель = " << denominator << endl;
	}
}

int Fraction::get_num()
{
	return numerator;
}

int Fraction::get_den()
{
	return denominator;
}

Fraction Fraction::operator+(const int& num) ////сложение с целым числом
{
	this->denominator = denominator;
	numerator = numerator + num * denominator;
}


Fraction Fraction::operator-(const int& num) //вычетание целого числа
{
	Fraction temp;
	temp.denominator = denominator;
	temp.numerator = numerator - num * denominator;
	return temp;
}

int main()
{
	setlocale(LC_ALL, "Ru-ru");

	cout << "Функционал Fraction and Fraction_v2" << endl;

	Fraction test = { 1,3 };
	cout << "Значения дроби введены автоматически = " ; test.show();
	Fraction_v2 Test = test;
	cout << "Fraction_v2 - наследник класса Fraction ; " << endl << " Можно объявлять объект типа Fraction_v2 , можно копировать значения Fraction в Fraction_v2 " << endl;
	Test = 5 + test;

	cout << "Есть прибавление числа к Fraction и Fraction к числу" << endl;
	Test.show();

	cout << "Вычитание из Fraction " << endl;
	test = test - 5;
	Test = Test - 5;
	cout << "Для вывода значений использовать метод show();" << endl;
	Test.show();
	return 0;
}
