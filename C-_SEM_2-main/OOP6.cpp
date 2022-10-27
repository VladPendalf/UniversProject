#include <iostream>
#include <fstream>
#include <string>
#include <exception>
#include <sstream>
//------------------ТЗ---------------------//
/*
1 Реализовать структуру для хранения представленных в задании данных (класс, представляющий Связный список, является шаблоном класса, в main его работа
демонстрируется на примере хранения объекта структуры/класса из Вашего варианта).
	Информация в элемент структуры вводится со стандартного потока ввода (предусмотреть автоматическое заполнение).
2 В классе Связный Список ввести деструктор.
	-Поля класса должны быть защищёнными (protected).
	-Ввести открытый интерфейс (public) для работы с ними.
	-Унаследовать класс списка от базового класса Связный список с ключевым словом public.
	-Переопределить функции push() и pop() – для добавления и извлечения элементов из списка.
	-Написать функцию вставки нового элемента в произвольное место списка insert(), удаления remove(),  | поиска элемента find() по значению | {что должна делать эта функция?}
	-Реализовать указанный вид поиска: под функцией фильтра предполагается поиск элементов, которые удовлетворяют условию element.field >, < value, под поиском – только
element.info==value (element.info – поле info в элементе списка element, value – искомое значение).
	-Фильтр возвращает новый список элементов, удовлетворяющих условию.
	-Функцию фильтра и поиска реализовать в итеративной и рекурсивной формах.
	-Класс, объекты которого хранятся в списке, указан в таблице 1
3 (*) Кроме фильтра по указанным полям, написать универсальный фильтр по произвольному полю, который принимает указатель на функцию. Эта функция
возвращает 1, если элемент удовлетворяет условию и 0 – в противном случае.
Структура «Человек».
Минимальный набор полей: фамилия, имя, пол, рост, вес, дата рождения, телефон, адрес.
Добавление: в конец (стек)
Удаление: с конца (стек)
Поиск по фамилии, фильтр по дате рождения.
4 Выделите память для списка динамически (используя указатель на базовый класс), а затем, в конце работы кода, освободите её.
	-Проверьте правильную работу деструкторов базового и производного классов (используйте виртуальный деструктор).
	-Преобразуйте указатель на базовый класс в указатель типа производного класса с помощью оператора dynamic_cast.
	-Проверьте работу деструкторов в случае выполнения операции освобождения памяти для преобразованного указателя.
5 Написать функции сохранения списка файл* save() и извлечения списка из файла* load().
	-Для ввода/вывода элемента списка в/из файла используйте переопределённые функции ввода/вывода в поток (сделайте различие между вводом/выводом в консоль и вводом/выводом в файл).
6 Введите манипулятор, форматирующий вывод, и примените его при выводе содержимого контейнера (таблица 2).
Вывод в научном виде, ширина поля – 5 символов, 2 знака после запятой
*/

using namespace std;

std::ostream& operator>>(std::ostream& s, const string& hz)
{
	return s >> hz;
}

std::ostream& operator>>(std::ostream& s, const bool& hz)
{
	return s >> hz;
}


struct date
{
	int day = 1, mounth = 1, years = 2021;

	date()
	{
		day = 1;
		mounth = 1;
		years = 2021;
	}
	date(int d, int m, int y) : day(d), mounth(m), years(y) {}
};

std::istream& operator>>(std::istream& s, date& hz)
{
	return s >> hz.day >> hz.mounth >> hz.years;
}

std::ostream& operator<<(std::ostream& s, const date& hz)
{
	return s << hz.day << hz.mounth << hz.years;
}

class Human //сделал класс, хотя, наверное, надо было сделать struct Human
{
public:
	string Surname = ("Крейнин")//фамилия
		, name = ("Роман")//имя 
		, adres = ("Столовка физтеха") //адрес
		, telephone = ("Samsung galaxy A52");//телефон

	date data; //дата рождения: день.месяц.год

	bool sex = 0; //пол: 0-fmale, 1-male

	double weight = 65//вес
		, height = 176; //рост

	Human()
	{
		Surname = ("Крейнин")//фамилия
			, name = ("Роман")//имя 
			, adres = ("Столовка физтеха") //адрес
			, telephone = ("Samsung galaxy A52");//телефон
		data;
		sex = 0;
		weight = 65;
		height = 176;
	}

	Human(string S_name, string name, bool sex, double height, double weight, date data, string telephone, string adres) :
		Surname(S_name), name(name), sex(sex), height(height), weight(weight), data(data), telephone(telephone), adres(adres) {}

	Human(const Human& hmn) :
		Surname(hmn.Surname), name(hmn.name), sex(hmn.sex), height(hmn.height), weight(hmn.weight), data(hmn.data), telephone(hmn.telephone), adres(hmn.adres) {}

	Human& operator=(const Human& hmn)
	{
		if (this != &hmn)
		{
			Surname = hmn.Surname;
			name = hmn.name;
			sex = hmn.sex;
			height = hmn.height;
			weight = hmn.weight;
			data = hmn.data;
			telephone = hmn.telephone;
			adres = hmn.adres;
		}	
			return *this;
	}


	friend ostream& operator<<(ostream& s, const Human& hmn)
	{
		s << "\nФамилия ->" << hmn.Surname << "\nИмя ->" << hmn.name << "\n.Пол ->" << hmn.sex << "\nРост ->" << hmn.height << "\nВес ->" << hmn.weight << "\nДата ->" << hmn.data
			<< "\nТелефон ->" << hmn.telephone << "\nАдрес ->" << hmn.adres;
		return s;
	}

	friend istream& operator>>(istream& s, Human& hmn)
	{
		s >> hmn.Surname >> hmn.name >> hmn.sex >> hmn.height >> hmn.weight >> hmn.data >> hmn.telephone >> hmn.adres;
		return s;
	}

};

template <typename T>
class Element
{
public:
	Element* next;
	Element* prev;
	T info;

	Element()
	{
		next = prev = nullptr;
	}
	Element(Element* Next, Element* Prev, T data)
	{
		next = Next;
		prev = Prev;
		info = data;
	}
	Element(const T& data)
	{
		next = prev = nullptr;
		info = data;
	}
	Element(const Element& el)
	{
		next = el.next;
		prev = el.prev;
		info = el.info;
	}

	friend ostream& operator<<(ostream& fout, Element<T>& el)
	{
		fout << el.info;
		return fout;
	}

	friend istream& operator>>(istream& fout, Element<T>& el)
	{
		fout << el.info;
		return fout;
	}
};

template<class T>
class LinkedList
{
protected:

	Element<T>* head;
	Element<T>* tail;

	int count;
public:

	LinkedList()
	{
		head = tail = nullptr;
		count = 0;
	}

	virtual Element<T>* pop() = 0;
	virtual Element<T>* push(T& value) = 0;

	Element<T>& operator[](int index)
	{
		Element<T>* current = head;

		for (int i = 0; current != nullptr && i < index; current = current->next, i++);
		return *current;
	}

	virtual bool isEmpty()
	{
		return (LinkedList<T>::count == 0);
	}
	virtual int get_count()
	{
		return this->count;
	}
	virtual Element<T>* get_head()
	{
		return this->head;
	}
	virtual Element<T>* get_tail()
	{
		return this->tail;
	}

	template<class T2>
	friend ostream& operator<<(ostream& fout, LinkedList<T2>& el)
	{
		Element<T2>* current;

		for (current = el.head; current != nullptr; current = current->next)
			fout << *current << "; ";

		return fout;
	}

	template<class T2>
	friend istream& operator>>(istream& fin, const LinkedList<T2>& el)
	{
		Element<T2>* current;

		for (current = el.head; current != nullptr; current = current->next)
			fin >> *current;
		return fin;
	}

	virtual ~LinkedList()
	{
		Element<T>* current = this->head;

		while (current != nullptr)
		{
			Element<T>* to_delete = current;
			current = current->next;
			delete to_delete;
		}
		this->head = nullptr;
		this->tail = nullptr;
		this->count = 0;
	}
};

template<class T>
class Stack : public LinkedList<T>
{
public:
	Stack<T>() : LinkedList<T>() {}

	Stack<T>(const Stack& stk)
	{
		this->count = 0;

		Element<T>* current = stk.head;
		Element<T>* cur = nullptr;

		while (current != nullptr)
		{
			if (cur == nullptr)
			{
				cur = new Element<T>(*current);
				this->head = cur;
				current = current->next;
			}
			else
			{
				cur->next = new Element<T>(*current);
				cur->next->prev = cur;
				cur = cur->next;
				current = current->next;
			}
			++(this->count);
		}
		this->tail = cur;
	}

	Stack& operator=(const Stack& stk) 
	{
		if (this != &stk)
		{
			while (!this->isEmpty())
			{
				Element<T>* ptr = this->pop();
				delete ptr;
			}

			this->count = 0;

			Element<T>* current = stk.head;
			Element<T>* current_this = nullptr;

			while (current != nullptr)
			{
				if (current_this == nullptr)
				{
					current_this = new Element<T>(*current);
					
					this->head = current_this;
					
					current = current->next;
				}
				else
				{
					current_this->next = new Element<T>(*current);
					current_this->next->prev = current_this;
					current_this = current_this->next;
					
					current = current->next;
				}
				++(this->count);
			}
			this->tail = current_this;
		}
		return *this;
	}

	virtual Element<T>* push(T& value)
	{
		if (this->isEmpty())
		{
			this->head = new Element<T>(value);
			this->tail = this->head;
			this->head->next = nullptr;
			this->head->prev = nullptr;
		}
		else
		{
			this->tail->next = new Element<T>(value);
			this->tail->next->prev = this->tail;
			this->tail = this->tail->next;
		}
		++(this->count);
		return this->tail;
	}

	virtual Element<T>* pop()
	{
		if (this->isEmpty())
		{
			return nullptr;
		}

		Element<T>* answ = this->tail;

		if (this->count == 1)
		{
			this->head = nullptr;
			this->tail = nullptr;
		}
		else
		{
			this->tail = this->tail->prev;
			this->tail->next = nullptr;
		}
		--(this->count);

		answ->prev = nullptr;

		return answ;
	}

	Element<T>* insert(const T& value, int index)
	{
		if (index <= this->count)
		{
			Element<T>* current = this->head;
			int current_num = 0;

			while (current_num < index)
			{
				current = current->next;
				++current_num;
			}

			if (current == this->head)
			{
				Element<T>* old = this->head;
				this->head = new Element<T>(value);
				this->head->next = old;
				old->prev = this->head;
				++(this->count);
				return this->head;
			}
			else if (current != nullptr)
			{
				Element<T>* old_prev = current->prev;

				current->prev = new Element<T>(value);
				current->prev->next = current;
				current->prev->prev = old_prev;
				old_prev->next = current->prev;
				++(this->count);
				return current->prev;
			}
			else
			{
				this->tail->next = new Element<T>(value);
				this->tail->next->prev = this->tail;
				this->tail = this->tail->next;
				++(this->count);
				return this->tail;
			}
		}
	}

	Element<T> remove(int index)
	{
		if (index < this->count)
		{
			Element<T>* current = this->head;
			int current_num = 0;

			while (current_num != index)
			{
				current = current->next;
				++current_num;
			}
			Element<T>* c_prev = current->prev;
			Element<T>* c_next = current->next;

			if (current == this->head)
			{
				this->head = this->head->next;
			}
			if (current == this->tail)
			{
				this->tail = this->tail->prev;
			}

			Element<T> answ(*current);
			answ.next = nullptr;
			answ.prev = nullptr;

			delete current;
			current = nullptr;

			if (c_prev != nullptr)
			{
				c_prev->next = c_next;
			}
			if (c_next != nullptr)
			{
				c_next->prev = c_prev;
			}

			--(this->count);
			return answ;

		}
	}

	template<typename T2>
	Stack filter(bool (*value)(const T& vs, const T2 value), const T2 id)
	{
		Stack<T> answ;

		Element<T>* current = this->head;

		while (current != nullptr)
		{
			if (value(current->info, id))
			{
				answ.push(current->info);
			}
			current = current->next;
		}
		return answ;
	}

	template<typename T2>
	Stack<T>* filter_recursive(bool (*value)(const T& vs, const T2 value), const T2 id, Element<T>* begin = nullptr, Stack<T>* begin_start = nullptr)
	{
		if (begin_start == nullptr && begin == nullptr)
		{
			begin = this->head;
			begin_start = new Stack<T>;
		}
		else if (begin_start == nullptr)
		{
			begin_start = new Stack<T>;
		}
		else if (begin == nullptr)
		{
			return begin_start;
		}
		else if (value(begin->info, id))
		{
			begin_start->push(begin->info);
		}

		return filter_recursive(value, id, begin->next, begin_start);
	}

	void save(ofstream& fout)
	{
		fout << this->count << endl;
		Element<T>* current = this->head;
		for (int i = 0; i < this->count; ++i)
		{
			fout << (*current) << endl;
			current = current->next;
		}
	}

	void load(ifstream& fin)
	{
		while (!this->isEmpty())
		{
			Element<T>* ptr = this->pop();
			delete ptr;
		}

		int vle = 0;
		string str;

		getline(fin, str); //считываем всю строку , т.к. getline() нормально обрабатывает пробелы
		std::istringstream foo(str); foo >> vle;

		for (int i = 0; i < vle; ++i)
		{
			T current;
			fin >> current;
			this->push(current);
		}

	}

	void print()
	{
		while (!this->isEmpty())
		{
			Element<T>* ptr = this->pop();

			cout << ptr->info << "\n";

			delete ptr;
		}
	}

	virtual ~Stack()
	{
		Element<T>* current = this->head;

		while (current != nullptr)
		{
			Element<T>* to_delete = current;
			current = current->next;
			delete to_delete;
		}
		this->head = nullptr;
		this->tail = nullptr;
		this->count = 0;
	}
};

bool surname_search(const Human& hmn, const string str = "") 
{
	if (hmn.Surname == str)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

bool birthday(const Human& p, date& data) //я знаю, что это так не работает
{
	if (p.data.day <= data.day && data.mounth <= data.mounth && data.years <= data.years)
	{
		return 1;
	}
	else {
		return 0;
	}
}

int main()
{
	setlocale(LC_ALL, "Ru-ru");
	try
	{
		Stack<Human> hmn;
		Human who, is, me;
		is.Surname = "Радужника";
		me.Surname = "Икзарена";
		hmn.push(who);
		hmn.push(is);
		hmn.push(me);

		hmn.remove(1);

		hmn.insert(is, 1);

		Stack<Human>* test = hmn.filter_recursive(surname_search, string("Крейнин"));
		Stack<Human> tesT = hmn.filter(surname_search, string("Крейнин"));

		hmn.print();
		test->print();

	}
	catch (...)
	{
		cerr << "Error";
	}

	try
	{
		Human who;

		LinkedList<Human>* arr = new Stack<Human>;
		delete arr;

		LinkedList<Human>* arr_1 = new Stack<Human>;
		Stack<Human>* arr_2 = dynamic_cast<Stack<Human>*>(arr_1);
		delete arr_2;

		Stack<Human> inf;
		Stack<Human> of;
		string sname = { "Surname" };
		string name = { "Name" };
		string telephone = { "9260242831" };
		string adres = { "Карась" };
		bool keks = 1;
		int height = 176, weight = 65;
		date data{ 12,12,2002 };

		Human people(sname, name, keks, height, weight, data, telephone, adres);

		inf.push(people);
		inf.push(who);
		inf.push(who);

		ofstream fout("text.txt");

		if (fout.is_open())
		{
			inf.save(fout);
			fout.close();
		}
		else
		{
			std::cout << "file not opened\n";
		}

		ifstream fin("text.txt");

		if (fin.is_open())
		{
			of.load(fin);
			fin.close();
		}
		else
		{
			std::cout << "file not opened\n";
		}

		of.print();
	}
	catch (...)
	{
		cerr << "Error2";
	}

	return 0;
}
