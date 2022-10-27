#include <iostream>
#include <algorithm>

using namespace std;


bool simple(int n) //проверка числа на простоту
{
	for (int i = 2; i <= n / 2; i++) if ((n % i) == 0) return false;
	return true;
}

/*======================ТЗ====================+
A.Вам предоставлен класс MyArrayParent, частично реализующий функции массива
(файл InheritanceArray_empty.cpp). Дополните класс необходимыми функциями:
	1 Конструктором копий MyArrayParent (&MyArrayParent v).
	2 Оператором =.
	3 Оператором [ ] для обращения к элементу по индексу.
	4 Конструктором, принимающим и копирующим информацию из существующего массива.

B. В классе MyArrayChild, унаследованном от класса MyArrayParent, необходимо
добавить функции (обратите внимание на то, что можно пользоваться функциями, уже
реализованными в базовом классе):
	1 Удаления элемента из произвольного места в массиве RemoveAt().
	2 Поиска элемента в массиве по значению IndexOf().
	3 Вставки элемента в некоторое место в массиве InsertAt().
	4 Добавьте функцию согласно Вашему варианту (см. таблицу 1). Результатом обработки массива должен
	быть новый объект класса. Исходный массив не должен меняться.

C. Унаследуйте новый класс MySortedArray от MyArrayChild. Мы предполагаем, что этот
класс содержит упорядоченный массив. Переопределите функции из пункта B.4, имея
ввиду, что массив отсортирован. Переопределите операцию добавления элемента (push)
таким образом, чтобы массив оставался отсортированным при добавлении элемента

B.4 Во входном массиве – целые числа. Поместить в массив на выходе только
простые числа из него


==============================================+
*/

class MyArrayParent
{
protected:

	int capacity; //сколько памяти выделено 

	int count; //количество элементов - сколько памяти используем

	double* ptr;//массив

public:

	//----------------------------КОНСТРУКТОРЫ_И_ДЕСТРУКТОРЫ---------------------------------+							 
	MyArrayParent(int Dimension);	//конструктор по умолчанию (но это не точно... :D )				 

	MyArrayParent(double* arr, int len); //конструктор принимает существующий массив	 

	MyArrayParent(const MyArrayParent& V); //конструктор копирования

	~MyArrayParent();
	//---------------------------------------------------------------------------------------+

		//обращение к полям
	int Capacity() { return capacity; } //размер общей памяти

	int Size() { return count; } //число элементов

	double GetComponent(int index); //вывод числа по индексу

	void SetComponent(int index, double value); //изменить значение числа по индексу

	virtual void push(double value); //добавить элемент в конец

	void RemoveLastValue(); //удаление элемента с конца

	double& operator[](int index); //вывести элемент по индексу

	MyArrayParent& operator=(const MyArrayParent& V); //перегрузка оператора =

	void print(); //вывод всего массива

};

class MyArrayChild : public MyArrayParent
{
public:

	MyArrayChild(int Dimension = 10) : MyArrayParent(Dimension) { cout << "\nMyArrayChild constructor with Dimension"; } //используем конструктор родителя

	~MyArrayChild();

	void RemoveAt(int index);//удаление элемента

	virtual int IndexOf(double value);//поиск элемента

	void InsertAt(double value, int index); //вставка элемента

	MyArrayChild& operator=(const MyArrayChild& str);

	MyArrayChild Easyl_num();
};

class MySortedArray : public MyArrayChild
{
protected:
	int IndexOf_1(double value);// бинарный поиск

public:
	MySortedArray(int Dimension = 10) : MyArrayChild(Dimension) { cout << "\nMySortedArray constructor\n"; }

	// using MyArrayChild::MyArrayChild -> что действительно делает и как это выглядит?

	~MySortedArray();

	int IndexOf(double value);// бинарный поиск

	void push(double value);

	MySortedArray Easyl_num();
};


MyArrayParent::MyArrayParent(int Dimension = 10)
{
	cout << "\nMyArrayParent constructor with Dimension";
	ptr = new double[Dimension]; // выделяем память с помощью new
	capacity = Dimension;
	count = 0;
}

MyArrayParent::MyArrayParent(double* arr, int len) //конструктор принимает существующий массив
{
	cout << "\nMyArrayParent constructor with array" << endl;

	capacity = len + 5;
	ptr = new double[capacity]; //делаем массив с запасом
	count = len;


	for (int i = 0; i < len; ++i)
	{
		ptr[i] = arr[i];
	}

	print();

}

MyArrayParent::MyArrayParent(const MyArrayParent& V)
{
	//создание копии объекта - в основном, при возвращении результата из функции / передаче параметров в функцию
	cout << "\nMyArrayParent constructor copy";
	capacity = V.capacity;
	count = V.count;

	ptr = new double[V.capacity];
	for (int i = 0; i < V.count; ++i)
		ptr[i] = V.ptr[i];

	print();
}

MyArrayParent::~MyArrayParent()
{
	cout << "\nMyArrayParent destructor";
	if (ptr != nullptr)
	{
		delete[] ptr; // освобождаем свободную память 
		ptr = nullptr;
	}
}

MyArrayChild::~MyArrayChild()
{
	cout << "\nMyArrayChild destructor\n";
	if (ptr != nullptr)
	{
		delete[] ptr;
		ptr = nullptr;
	}
}

MySortedArray::~MySortedArray()
{
	if (ptr != NULL)
	{
		delete[] ptr; // освобождаем свободную память 
		ptr = NULL;
	}
	cout << "\nMySortedArray destructor\n";
}

double MyArrayParent::GetComponent(int index)
{
	if (index >= 0 && index < count) { return ptr[index]; }
	else return -1;
}

void MyArrayParent::SetComponent(int index, double value) //добавить throw()
{
	if (index >= 0 && index < count)
		ptr[index] = value;
	else
		cout << "Error\n";

}

void MyArrayParent::push(double value)
{
	if (capacity > count)
	{
		ptr[count] = value;
		count += 1;
	}
	else
		cout << "No any space left!" << endl;
}

void MyArrayParent::RemoveLastValue()
{
	if (count > 0)
		count -= 1;
}

double& MyArrayParent::operator[](int index)
{
	if (index < 0)
		return ptr[count + index];
	if (count > index)
		return ptr[index];
}

MyArrayParent& MyArrayParent::operator=(const MyArrayParent& V)
{
	if (this != &V)
	{
		capacity = V.capacity;
		count = V.count;
		delete[] ptr;

		ptr = new double[V.capacity];
		for (int i = 0; i < V.count; ++i)
			ptr[i] = V.ptr[i];
		// отличие от копирования - нужно вернуть this
	}
	else
	{
		return *this; //указатель сам на себя 
	}
}

void MyArrayParent::print()
{
	cout << "\nMyArrParent, size = " << count << "\n values: { ";

	for (int i = 0; i < (count - 1); ++i)
	{
		cout << ptr[i] << " , ";
	}
	cout << ptr[count - 1] << " }\n";
}

void MyArrayChild::RemoveAt(int index)
{
	if (abs(index) < count)
	{
		if (index > 0)
		{
			for (int i = index; i < count; i++)
			{
				ptr[i] = ptr[i + 1];
			}
			count -= 1;
		}
		if (index < 0)
		{
			for (int i = count + index; i < count; i++)
			{
				ptr[i] = ptr[i + 1];
			}
		}
	}
}

int MyArrayChild::IndexOf(double value)
{
	for (int i = 0; i < count; i++)
		if (ptr[i] == value)
			return i;
	return -1;
}

void MyArrayChild::InsertAt(double value, int index)
{
	if (index > 0)
	{
		for (int i = count - 1; i >= index; i--)
		{
			ptr[i + 1] = ptr[i];
		}
		ptr[index] = value;
		count++;
	}
}

MyArrayChild MyArrayChild::Easyl_num()
{
	MyArrayChild arr_es_num; //объект класса

	arr_es_num.count = count;
	arr_es_num.capacity = capacity;

	for (int i = 0, j = 0; i < count; ++i) //проверяем на простоту
	{
		if (simple(ptr[i]) == true)
		{
			arr_es_num.ptr[j] = ptr[i];
			++j;
		}
		else
		{
			arr_es_num.count--;
		}
	}
	return arr_es_num;
}

MyArrayChild& MyArrayChild::operator=(const MyArrayChild& str)
{
	if (this != &str)
	{
		count = str.count;
		capacity = str.capacity;
		delete[] ptr;

		ptr = new double[capacity];
		for (int i = 0; i < count; ++i)
		{
			ptr[i] = str.ptr[i];
		}
	}
	else
	{
		return *this;
	}
}

void MySortedArray::push(double value)
{
	if (count == 0)
	{
		ptr[count] = value;
		count += 1;
	}
	else
	{
		int index = IndexOf_1(value);
		InsertAt(value, index);
	}
}

int MySortedArray::IndexOf_1(double value)
{
	int l = 0;
	int r = count;
	int mid = 0;

	while (l <= r)
	{
		mid = (l + r) / 2;
		if (ptr[mid] == value)
			return mid;
		if (value < ptr[mid])
			r = mid - 1;
		if (value > ptr[mid])
			l = mid + 1;
	}
	return mid;
}

int MySortedArray::IndexOf(double value)
{
	int l = 0;
	int r = count;
	int mid;

	while (l <= r)
	{
		mid = (l + r) / 2;
		if (ptr[mid] == value)
			return mid;
		if (value < ptr[mid])
			r = mid - 1;
		if (value > ptr[mid])
			l = mid + 1;
	}
	return -1;
}

MySortedArray MySortedArray::Easyl_num()
{
	MySortedArray arr_es_num; //объект класса

	arr_es_num.count = count;
	arr_es_num.capacity = capacity;

	for (int i = 0,j = 0; i < count; ++i) //проверяем на простоту
	{
		if (simple(ptr[i]) == true)
		{
			arr_es_num.ptr[j] = ptr[i];
			++j;
		}
		else
		{
			arr_es_num.count--;
		}
	}
	return arr_es_num;
}

int main()
{
	setlocale(LC_ALL, "Ru-ru");

	MyArrayParent arr;

	for (int i = 0; i < 6; ++i)
	{
		arr.push(i);
	}
	arr.print();

	MyArrayChild test, es_num;
	for (int i = 0; i < 6; ++i)
	{
		test.push(i);
	}
	test.print();

	int index;
	test.InsertAt(5, 5);
	index = test.IndexOf(5);
	cout << "\nIndex = " << index << endl;

	test.print();

	es_num = test.Easyl_num();

	es_num.print();
	test.print();
	return 0;
}
