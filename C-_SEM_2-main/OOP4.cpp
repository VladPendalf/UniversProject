#include <iostream>
#include <tchar.h>

using namespace std;
/*
Унаследуйте свой класс от базового класса «Строка». Реализуйте работу функций:
конструкторов, конструктора копий, деструктора, operator=, как в базовом классе, так и в
наследнике. Добавьте в наследник работу функции, указанной в варианте.

Написать функцию поиска IndexOf() первого вхождения произвольной
подстроки в строке.
*/
class BaseString
{
protected:
	char* p = nullptr; //указатель 
	int len = 0; //число символов
	int capacity = 256; //макс размер
public:
	BaseString(char* ptr) //Kонструктор
	{

		p = new char[capacity];
		
		p[len] = '\0';
		
		if (ptr != nullptr) //проверка на ненулевую строку
		{
			while (ptr[len] != '\0' && len < (capacity - 1)) //копируем данные в новый массив
			{
				p[len] = ptr[len];
				++len;
			}

			p[len] = '\0'; //отделяем 
			
		}
	}
 BaseString(char* ptr, int len) //Kонструктор
	{
                capacity = len*2;
		p = new char[capacity];
		
		p[len] = '\0';
		
		if (ptr != nullptr) //проверка на ненулевую строку
		{
			while (ptr[len] != '\0' && len < (capacity - 1)) //копируем данные в новый массив
			{
				p[len] = ptr[len];
				++len;
			}

			p[len] = '\0'; //отделяем 
			
		}
	}
	BaseString()
	{
		p = new char[capacity];
		
		p[len] = '\0';
	}

	BaseString(const char* ptr, int len)
	{
		capacity = 2 * len;
		p = new char[capacity];
		
		p[len] = '\0';
		
		if (ptr != nullptr) 
		{
			while (ptr[len] != '\0' && len < (capacity - 1))
			{
				p[len] = ptr[len];
				++len;
			}

			p[len] = '\0';
		}
	}

	BaseString(int Capacity)
	{

		capacity = Capacity;
		
		p = new char[capacity];
		
	}

	~BaseString() //деструктор
	{
		
		if (p != nullptr)
		{
			delete[] p;
		}
		
		len = 0;
	}
	
	int Length() { return len; } //число букв
	
	int Capacity() { return capacity; } //макс размер
	
	char* get() {return p;} //указатель на первый элемент

	char& operator[](int& i) //перегрузка оператора, для вывода символа по его индексу 
	{ 
		return p[i];
	} 
	
	BaseString& operator=(const BaseString& s) //перегрузка оператора =
	{

		if (this != &s)
		{
			capacity = s.Capacity();

			len = s.Length();
                        if(p != nullptr)
                            delete[] p;

                         p=new char[Capacity()];
			for (int i = 0; i < len; i++)
			{
				p[i] = s.p[i];
			}

			p[len] = '\0';
		}
			return *this;
	}
	
	BaseString(const BaseString& s)//конструктор копирования 
	{
		
			len = s.Length();
			capacity = s.Capacity();

			p = new char[capacity];

			for (int i = 0; i < len; i++)
			{
				p[i] = s.p[i];
			}

			p[len] = '\0';
	}
	
	virtual void print() //виртуальная функция вывода
	{
		int i = 0;

		while (p[i] != '\0')
		{
			cout << p[i] << ',' << ' ';
			i++;
		}

		cout << ";\n";
	}
};


class String : public BaseString
{
public:

	using BaseString::BaseString; //с++ 11 - это 1000 и 1 отсутствующий конструктор :)

	int IndexOf(String& str)
	{
		bool fl = false;
		int i = 0, j = 0, index;

		while (j < str.Length() && i < len)
		{
			if (p[i] == str.p[j])
			{
				fl = true;
				if (p[i] == str.p[0])
					index = i;
				++j;
			}
			else
			{
				fl = false;
				j = 0;
				index = 0;
			}
			++i;
		}

		if (fl && j == str.Length())
		{
			cout << "Индекс подстроки = ";
			return index;
		}
		else
		{
			return -1;
		}

	}
};


int _tmain(int argc, _TCHAR* argv[]) //без #include <tchar.h> работать не будет... 
{
	setlocale(LC_ALL, "Ru-ru");

	String str("acdacbdabcd"), test("abcd");
	int i;

	i = str.IndexOf(test);

	cout << i;


	return 0;
}


