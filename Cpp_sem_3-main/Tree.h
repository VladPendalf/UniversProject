#pragma once
#include <iostream>
#include <vector>
class TreeIterator;

enum NodeColor { Black, Red };

class RBNode
{
public:
	RBNode(int value, 
		   NodeColor color, 
		   RBNode*	left    = nullptr, 
		   RBNode*	right   = nullptr, 
		   RBNode*	parent  = nullptr) :
		_value(value),
		_color(color),
		_parent(parent),
		_left(nullptr),
		_right(nullptr)
	{ }

public:
	int _value;

	NodeColor _color; //base black

	RBNode* _parent,
		  * _left,
		  * _right;
};

class TreeIterator : public std::iterator<std::input_iterator_tag, RBNode> {
	RBNode* node;

public:
	TreeIterator(RBNode* node_ = nullptr) : node(node_) {}
	TreeIterator(const TreeIterator& it) : node(it.node) {}

	bool operator == (const TreeIterator& other) const { return node == other.node; }
	bool operator != (const TreeIterator& other) const { return node != other.node; }

	int& operator * () { return node->_value; }
	const int& operator * () const { return node->_value; }

	TreeIterator& operator++() {
		if (node->_right)
		{
			node = node->_right;
			while (node->_left)
			{
				node = node->_left;
			}
		}
		else
		{
			RBNode* temp = node->_parent;
			while (temp && temp->_right == node)
			{
				node = temp;
				temp = node->_parent;
			}

			// Если корневой узел дерева не имеет правого потомка и итератор начинается с корневого узла
			if (node->_right != temp)
				node = temp;
		}
		return *this;
	}
	TreeIterator operator++(int) {
		TreeIterator old(node);
		++* this;
		return old;
	}

	TreeIterator& operator--() {
		if (node->_left)
		{
			node = node->_left;
			while (node->_right)
			{
				node = node->_right;
			}
		}
		else
		{
			RBNode* temp = node->_parent;
			while (temp && temp->_left == node)
			{
				node = temp;
				temp = node->_parent;
			}

			node = temp;
		}
		return *this;
	}
	TreeIterator operator--(int) {
		TreeIterator old(node);
		--* this;
		return old;

	}

};

class RBTree
{
public:
	RBTree() : root(nullptr) {}  //конструктор по умолчанию
	RBTree(std::vector<int>& v)  //инициализурующий конструктор
	{ 
		if (!v.empty()) //если массив не пустой
		{
			for (auto it : v) //последовательно инициализируем его числа
				InsertNode(it);
		}
	}

	void InsertNode(int value) {
		
		RBNode* t = new RBNode(value, Red); //выделяем память под новый элемент
		
		RBNode* p = root;
		RBNode* q = nullptr;
			
		while (p) { // спускаемся вниз, пока не дойдем до листа 
			q = p;
			if (t->_value > p->_value)
				p = p->_right;
			else
				p = p->_left;
		}
		t->_parent = q;
		// добавляем новый элемент красного цвета 
		if (q) {
			if (t->_value > q->_value)
				q->_right = t;				
			else
				q->_left = t;
		}
		else //в дереве не было элементов и новый элемент становится корнем
			root = t;
		t->_color = Red;
		fixInsertion(t); // проверяем, не нарушены ли свойства красно-черного дерева 
	}

	void fixInsertion(RBNode* node) {
		RBNode* parent = node->_parent; //отец
		while (node != RBTree::root && parent->_color == Red) //если есть красный отец
		{
			RBNode* gparent = parent->_parent; //дед
			if (gparent->_left == parent) // отец находится слева от деда
			{
				RBNode* uncle = gparent->_right; //дядя
				if (uncle && uncle->_color == Red) //если есть красный дядя, то меняем цвет отца и дяди на черный,
												   //а цвет деда на красный
				{
					parent->_color = Black;
					uncle->_color = Black;
					gparent->_color = Red;
					node = gparent;
					parent = node->_parent;
				}
				else
				{
					if (parent->_right == node) //если выполнить перекрашивание выше, можно нарушить свойство дерева, поэтому
												//если добавляемый элемент был правым потомком, то делаем левый поворот
					{
						TurnLeft(root, parent);
						std::swap(node, parent);
					}
					TurnRight(root, gparent);  //балансируем
					gparent->_color = Red;
					parent->_color = Black;
				}
			}
			else // отец находится справа от деда
			{
				RBNode* uncle = gparent->_left;
				if (uncle && uncle->_color == Red)
				{
					gparent->_color = Red;
					parent->_color = Black;
					uncle->_color = Black;

					node = gparent;
					parent = node->_parent;
				}
				else
				{
					if (parent->_left == node)
					{
						TurnRight(root, parent);
						std::swap(parent, node);
					}
					TurnLeft(root, gparent);
					parent->_color = Black;
					gparent->_color = Red;
				}
			}
		}
		root->_color = Black; //корень всегда чёрный
	}

	~RBTree() {
		Destroy(root);
	}

	void TurnLeft(RBNode*& a, RBNode* b) {
		RBNode* y = b->_right;
		b->_right = y->_left;
		if (y->_left)
			y->_left->_parent = b;

		y->_parent = b->_parent;
		if (!b->_parent)
			a = y;
		else {
			if (b == b->_parent->_left)
				b->_parent->_left = y;
			else
				b->_parent->_right = y;
		}
		y->_left = b;
		b->_parent = y;
	}

	void TurnRight(RBNode*& a, RBNode* b) {
		RBNode* y = b->_left;
		b->_left = y->_right;
		if (y->_right)
			y->_right->_parent = b;

		y->_parent = b->_parent;
		if (!b->_parent)
			a = y;
		else {
			if (b == b->_parent->_right)
				b->_parent->_right = y;
			else
				b->_parent->_left = y;
		}
		y->_right = b;
		b->_parent = y;
	}

	void Destroy(RBNode* node) {
		if (!node)
			return void();

		Destroy(node->_left);
		Destroy(node->_right);

		delete node;
		node = nullptr;
	}

	void Remove(int value) {
		RBNode* deleteNode = Search(value);
		if (!deleteNode) //такого узла нет, выходим из удаления
			return void();
		
		RBNode* child
			, * parent;

		NodeColor color;

		if (deleteNode->_left && deleteNode->_right) // Левый и правый узлы удаленного узла не пусты (не конечные узлы)
		{
			RBNode* replace = deleteNode;

			// Найти узел-преемник (самый нижний левый узел правого поддерева текущего узла)
			replace = deleteNode->_right;
			while (replace->_left)
			{
				replace = replace->_left;
			}

			// Случай, когда удаленный узел не является корневым узлом
			if (deleteNode->_parent)
			{
				if (deleteNode->_parent->_left == deleteNode)
					deleteNode->_parent->_left = replace;
				else
					deleteNode->_parent->_right = replace;
			}
			// Ситуация с корневым узлом
			else
				root = replace;


			// child - это правильный узел, который заменяет узел и является узлом, который требует последующей корректировки
			// Поскольку замена является преемником, он не может иметь левого дочернего узла
			// Аналогично, у узла-предшественника не может быть правого дочернего узла
			child = replace->_right;
			parent = replace->_parent;
			color = replace->_color;

			// Удаленный узел является родительским узлом замещающего узла (repalce)
			if (parent == deleteNode)
				parent = replace;
			else
			{
				// Существование дочернего узла
				if (child)
					child->_parent = parent;
				parent->_left = child;

				replace->_right = deleteNode->_right;
				deleteNode->_right->_parent = replace;
			}
			replace->_parent = deleteNode->_parent;
			replace->_color = deleteNode->_color;
			replace->_left = deleteNode->_left;
			deleteNode->_left->_parent = replace;
			if (color == Black)
				RemoveFix(child, parent);

			delete deleteNode;
			return;
		}

		// Когда в удаленном узле только левый (правый) узел пуст, найдите дочерний узел удаленного узла
		if (deleteNode->_left)
			child = deleteNode->_left;
		else
			child = deleteNode->_right;

		parent = deleteNode->_parent;
		color = deleteNode->_color;

		if (child)
		{
			child->_parent = parent;
		}

		// Удаленный узел не является корневым узлом
		if (parent)
		{
			if (deleteNode == parent->_left)
				parent->_left = child;
			else
				parent->_right = child;
		}
		// Удаленный узел является корневым узлом
		else
			RBTree::root = child;

		if (color == Black)
		{
			RemoveFix(child, parent);
		}

		delete deleteNode;
	}

	void RemoveFix(RBNode* node, RBNode* parent ) {
		if (root) {
			RBNode* othernode;
			while ((!node) || node->_color == Black && node != RBTree::root)
			{
				if (parent->_left == node)
				{
					othernode = parent->_right;
					if (othernode->_color == Red)
					{
						othernode->_color = Black;
						parent->_color = Red;
						TurnLeft(root, parent);
						othernode = parent->_right;
					}
					else
					{
						if (!(othernode->_right) || othernode->_right->_color == Black)
						{
							othernode->_left->_color = Black;
							othernode->_color = Red;
							TurnRight(root, othernode);
							othernode = parent->_right;
						}
						othernode->_color = parent->_color;
						parent->_color = Black;
						othernode->_right->_color = Black;
						TurnLeft(root, parent);
						node = root;
						break;
					}
				}
				else
				{
					othernode = parent->_left;
					if (othernode->_color == Red)
					{
						othernode->_color = Black;
						parent->_color = Red;
						TurnRight(root, parent);
						othernode = parent->_left;
					}
					if ((!othernode->_left || othernode->_left->_color == Black) && (!othernode->_right || othernode->_right->_color == Black))
					{
						othernode->_color = Red;
						node = parent;
						parent = node->_parent;
					}
					else
					{
						if (!(othernode->_left) || othernode->_left->_color == Black)
						{
							othernode->_right->_color = Black;
							othernode->_color = Red;
							TurnLeft(root, othernode);
							othernode = parent->_left;
						}
						othernode->_color = parent->_color;
						parent->_color = Black;
						othernode->_left->_color = Black;
						TurnRight(root, parent);
						node = root;
						break;
					}
				}
			}
			if (node)
				node->_color = Black;
		}
		else
			return void();
	}
	void print() {
		if (!root)
			std::cout << "empty RBtree\n";
		else
			print(root);
	}
	void print(RBNode* node) const {
		if (!node)		
			return void();
		if (!node->_parent)
			std::cout << node->_value << "(" << node->_color << ") is root" << std::endl;
		else if (node->_parent->_left == node)
		{
			std::cout << node->_value << "(" << node->_color << ") is " << node->_parent->_value << "'s " << "left child" << std::endl;
		}
		else
		{
			std::cout << node->_value << "(" << node->_color << ") is " << node->_parent->_value << "'s " << "right child" << std::endl;
		}
		print(node->_left);
		print(node->_right);
	}

	RBNode* Search(int value)
	{
		RBNode* temp = root;
		if (temp->_value == value)
			return temp;
		
		while (temp)
		{
			if (temp->_value > value)
				temp = temp->_left;
			else if (temp->_value < value)
				temp = temp->_right;
			else
				break;
		}
		return temp;
	}
	
	RBNode* Min()
	{
		RBNode* temp = root;
		if (!temp) return nullptr;
		while (temp->_left)
		{
			temp = temp->_left;
		}
		return temp;
	}

	RBNode* Max()
	{
		RBNode* temp = root;
		if (!temp) return nullptr;
		while (temp->_right)
		{
			temp = temp->_right;
		}
		return temp;
	}

	TreeIterator begin() { return TreeIterator(Min()); }
	TreeIterator end() { return TreeIterator(); }
private:
	RBNode* root;
	friend TreeIterator;
};
