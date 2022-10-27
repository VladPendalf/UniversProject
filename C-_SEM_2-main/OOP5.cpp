#include <iostream>
#include <fstream>
#include <exception>
#include <string>
#include <typeinfo>
#include <iomanip>

using namespace std;


/*
1 Унаследуйте класс от базового класса Многомерный массив. Убедитесь что в родительском классе верно выделяется и освобождается память под многомерный массив. В производном
классе напишите метод заполнения массива произвольным нетривиальным образом. Введите метод, который решает задачу, указанную в варианте, и возвращает из неё результат (входная
матрица остаётся неизменной, на выходе должен быть новый массив или число).
2 Введите систему исключений, указанную на рисунке 1 Встройте собственный тип исключения, которое может возникнуть при
решении задачи из Вашего варианта, в общую структуру наследования. Продемонстрируйте обработку исключений с
помощью операторов try – throw – catch (исключения генерируются в методах класса Матрица, обрабатываются – в main).
3 Сохраните результат обработки нескольких матриц в файл, извлеките результаты из файла, выведите их в консоль. Продемонстрируйте, что
результаты, которые записывались в файл, и прочитанные из файла данные не отличаются.
4 Введите конструкторы и методы для чтения матрицы произвольного размера из файла.
5 Преобразуйте классы многомерных массивов к шаблонам классов.

Получить вектор, в котором содержатся максимальные элементы из каждой строки матрицы. -> .Max_Vector()
*/

//------------------Наследование класса ошибок-------------------//
/*
				std::exception
					 ^
					 |
					 |
					 |
 				     Exception
 				    ^        ^
				   /          \
				  /            \
				 /              \
			IndexOutOfBounds        WrongDimensionsException
		 	Exception                         ^
							  |
			  			          |
			 			          |
						    WrongSizeException
*/
//-------------------------------------------------------------//



class Exception : public exception
{
protected:
	string err;
public:
	Exception(const char* str)
	{
		err = string(str);
	}

	Exception(string& str)
	{
		err = str;
	}

	Exception(const Exception& err)
	{
		this->err = err.err;
	}

	virtual ~Exception() {};

	virtual void print() const
	{
		cout << "\nError - " << err << endl;
	}
};

class IndexOutOfBoundsException : public Exception
{
protected:
	int row, columns;
public:
	IndexOutOfBoundsException(string str, int& r, int& clmn) : Exception(str)
	{
		row = r;
		columns = clmn;
	}

	virtual void print() const
	{
		cout << err << "\nЭлемент в строке ->" << row << " и столбике -> " << columns << " вышел за пределы матрицы\n\a";
	}

};

class WrongDimensionsException : public Exception
{
protected:
	int r_1, c_1, r_2, c_2;
public:
	WrongDimensionsException(string str, int r1, int c1, int r2, int c2) : Exception(str), r_1(r1), r_2(r2), c_1(c1),c_2(c2) {}

	virtual void print() const
	{
		cout << err << "\nОперации с данными размерами матриц: A( " << r_1 << " , " << c_1 << " ) и B( " << r_2 << " , " << c_2 << " ) невозможны\n\a";
	}
};

//наследую от базового класса, т.к. задание : "Получить вектор, в котором содержатся максимальные элементы из каждой строки матрицы" - не связанно с двумя матрицами.
class WrongSizeException : public Exception
{
protected:
	int rw, cl;
public:
	WrongSizeException(string str, int r, int c) : Exception(str), rw(r), cl(c) { }

	virtual void print() const
	{
		cout << err << "\nВы ввели неккоректные размеры матрицы -> ( " << rw << " , " << cl << ")\n\a";
	}
};

class IncorrectDataInMatrix : public Exception
{
private:
	int r, c;
public:
	IncorrectDataInMatrix(string str, int rw, int cl) : Exception(str), r(rw), c(cl) {}

	virtual void print() const
	{
		cout << err << "\nВы ввели неккоректные данные в матрицу, элемент -> < " << r << " , " << c << " >\n\a";
	}
};

template <typename temp>
class BaseMatrix
{
protected:
	temp** arr;
	int row, columns;
public:
	BaseMatrix(int r = 2, int cl = 2) : row(r), columns(cl)
	{
		if (row <= 0 || columns <= 0)
		{
			throw WrongSizeException("Ошибка в размерах матрицы", row, columns);
		}

		//создание массива
		arr = new temp * [row];

		for (int i = 0; i < row; ++i)
		{
			arr[i] = new temp[columns];
		}
	}

	BaseMatrix(const BaseMatrix& matrix)
	{
		row = matrix.row;
		columns = matrix.columns;


		arr = new temp* [row];

		for (int i = 0; i < row; ++i)
		{
			arr[i] = new temp[columns];
		}

		for (int i = 0; i < row ; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				arr[i][j] = matrix.arr[i][j];
			}
		}
	}

	virtual ~BaseMatrix()
	{
		if (arr != nullptr) 
		{
			for (int i = 0; i < row; ++i)
			{
				delete[] arr[i];
			}
			delete[] arr;
			arr = nullptr;
		}
	}

	virtual void print()
	{
		for (int i = 0; i < row; ++i)
		{
			for (int j = 0; j < columns; ++j)
			{
				cout << std::left << std::setw(9) << std::setprecision(3) << arr[i][j] << ' ';
			}
			cout << '\n';
		}
	}

	BaseMatrix& operator=(const BaseMatrix& mtr)
	{
		if (this != &mtr)
		{
			if (arr != nullptr)
			{
				for (int i = 0; i < row; ++i)
					delete[] arr[i];
				delete[] arr;
			}

			row = mtr.row;
			columns = mtr.columns;

			arr = new temp * [row];
			for (int i = 0; i < row; i++)
			{
				arr[i] = new temp[columns];
			}

			for (int i = 0; i < row; i++)
			{
				for (int j = 0; j < columns; j++)
				{
					arr[i][j] = mtr.arr[i][j];
				}
			}
		}
			return *this;
	}

	virtual temp& operator()(int rw, int cln) const
	{
		if (rw < 0 || cln < 0 || rw > row || cln > columns)
		{
			throw IndexOutOfBoundsException("Ошибка в обращении по индексу -> ", rw, cln);
		}
		return arr[rw][cln];
	}

	template<typename T1>
	friend ostream& operator<<(ostream& out, BaseMatrix<T1>& matrix)
	{
		if (typeid(out) != typeid(ofstream)) 
		{
			for (int i = 0; i < matrix.row; i++) 
			{
				for (int j = 0; j < matrix.columns; j++) 
				{
					out << matrix.arr[i][j] << " ";
				}

				out << "\n";
			}
		}
		else 
		{
			out << " " << matrix.row << " " << matrix.columns << " ";
			
			for (int i = 0; i < matrix.row; i++) 
			{
				for (int j = 0; j < matrix.columns; j++)
				{
					out << matrix.arr[i][j];
					
					if (matrix.row != i + 1 || matrix.columns != j + 1)
					{
						out << " ";
					}
				}
			}
		}

		return out;
	}

	template<typename T1>
	friend istream& operator>>(istream& in, BaseMatrix<T1> matrix)
	{
		if (typeid(in) != typeid(ifstream)) 
		{
			for (int i = 0; i < matrix.row; i++)
			{
				for (int j = 0; j < matrix.columns; j++)
				{
					try 
					{
						in >> matrix.arr[i][j];
					}
					catch (...) 
					{
						cout << "Неверный ввод\n";
					}
				}
			}
		}
		else 
		{
			int row, columns;
			
			in >> row >> columns;
			
			if (row == matrix.row && columns == matrix.columns)
			{
				for (int i = 0; i < matrix.row; i++)
				{
					for (int j = 0; j < matrix.columns; j++)
					{
						try 
						{
							in >> matrix.arr[i][j];
						}
						catch (...) 
						{
							cout << "Неверный ввод\n";
						}
					}
				}

			}
			else {
				if (in.eof()) {
					cout << "Нет элементов\n";
				}
				else {
					cout << "Размеры не совпадают\n";
				}

			}
		}

		return in;
	}

};

template<typename T1>
class Matrix : public BaseMatrix<T1>
{
public:
	Matrix(int row = 2, int columns = 2) : BaseMatrix<T1>(row, columns) {}

	Matrix(istream& in)
	{
		in >> this->row >> this->columns;

		if (this->row <= 0 || this->columns <= 0)
		{
			throw WrongSizeException("Ошибка в размерах матрицы -> ", this->row, this->columns);
		}

		this->arr = new T1 * [this->row];

		for (int i = 0; i < this->row; ++i)
		{
			this->arr[i] = new T1[this->columns];
		}

		for (int i = 0; i < this->row; i++)
		{
			for (int j = 0; j < this->columns; ++j)
			{
				in >> this->arr[i][j];
			}
		}
	}

	void rewrite_matrix(istream& in)
	{
		if (this->arr != nullptr)
		{
			for (int i = 0; i < this->row; ++i)
			{
				delete[] this->arr[i];
			}
			delete[] this->arr;
			this->arr = nullptr;
		}

		in >> this->row >> this->columns;

		if (this->row <= 0 || this->columns <= 0)
		{
			throw WrongSizeException("Ошибка в размерах матрицы -> ", this->row, this->columns);
		}
		
		this->arr = new T1 * [this->row];
		for (int i = 0; i < this->row; ++i)
		{
			this->arr[i] = new T1[this->columns];
		}

		for (int i = 0; i < this->row; ++i)
		{
			for (int j = 0; j < this->columns; ++j)
			{
				in >> this->arr[i][j];
			}
		}
	}

	Matrix<T1> Max_Vector()
	{
		T1* tmp = new T1[this->row]; //массив макс значений из каждой строки матрицы

		for (int i = 0; i < this->row; ++i)
		{
			tmp[i] = this->arr[i][0];
		}

		for (int i = 0; i < this->row; ++i)
		{
			for (int j = 0; j < this->columns; j++)
			{
				if (tmp[i] <= this->arr[i][j])
				{
					tmp[i] = this->arr[i][j]; //заполняем массив
				}
			}
		}

		Matrix<T1> answer(this->row, 1); //матрица ответа

		for (int i = 0; i < answer.row; ++i)
		{ 
			answer.arr[i][0] = tmp[i]; //заполняем матрицу ответа
		}

		delete[] tmp; //очищаем массив макс значений

		return answer;
	}

	void RandomNums()
	{
		for (int i = 0; i < this->row; ++i)
		{
			for (int j = 0; j < this->columns;++j)
			{
				this->arr[i][j] = (T1)((rand()% 100));
			}
		}
	}

	//не знаю почему , но он не видит ф-ию print() из родительского класса
	virtual void print()
	{
		for (int i = 0; i < this->row; ++i)
		{
			for (int j = 0; j < this->columns; ++j)
			{
				cout << std::left << std::setw(9) << std::setprecision(3) << this->arr[i][j] << ' ';
			}
			cout << '\n';
		}
	}
};

int main()
{
	setlocale(LC_ALL, "Ru-ru");

	ofstream out("test_OOP5.txt");

	Matrix<int> answ(3, 1);
	Matrix<int> m1(3, 3);
	m1.RandomNums();

	m1.print();

	answ = m1.Max_Vector();

	if (out.is_open())
	{
		out << answ;
		out.close();
	}

	ifstream in("test_OOP5.txt");

	Matrix<int> txt(in);
	in.close();

	answ.print();

	cout << '\n';

	txt.print();

	try
	{
		Matrix<int>	m1(-5, 0);
	}
	catch (WrongSizeException gg)
	{
		gg.print();
	}
	catch (...)
	{
		cout << "\nSupFast Bug\a\n";
	}

	try
	{
		answ(1, 5);
	}
	catch (IndexOutOfBoundsException gg)
	{
		gg.what();
	}
	catch (...)
	{
		cout << "\nSupFast Bug\a\n";
	}


	return 0;
}
