#include <cassert>
#include <iostream>
#include <string>

//интересная ссылка (я не понимаю, как работают повороты)
//https://github.com/Bibeknam/algorithmtutorprograms/blob/master/data-structures/avl-trees/AVLTree.cpp

///
/// Домашнее задание:
///
/// 1.  Добавить findMin() и findMax() в классе Node, аналогичные таковым в Tree;
///     они должны искать в поддереве, корнем которого является текущий узел.
///
/// 2.  Реализовать малый правый поворот, а также большие левый и правый повороты
///     в классе Tree, по аналогии с малым левым поворотом.
///
/// 3.  Реализовать префиксный оператор «++» для итератора.
///
/// 4.  Реализовать Tree::findClosest() и Tree::deleteNode().
///
/// 5.  Реализовать юнит-тесты на все публичные методы классов Tree и TreeIterator,
///     кроме тривиальных. Прогонять эти тесты в функции main().
///

/**
1. Добавление.
    а) (интерфейсный способ) Создаём дерево, вызываем addNode(), проверяем:
        * что элемент добавился?
        * что элемент добавился по соседству с определёнными другими элементами?
        * сравнить дерево целиком с эталоном?
    б) (инвазивный) Конструируем объекты Node и Tree вручную, затем вызываем addNode(), проверяем (то же).
2. Удаление.
    а) Создаём дерево, вызываем removeNode(), проверяем:
        * что элемента в дереве больше нет?
        * что бывшие соседи элемента получили определённое новое состояние?
        * сравнить дерево целиком с эталоном?
    б) Конструируем объекты Node и Tree вручную, затем вызываем removeNode(), проверяем (то же).
3. Проход по дереву.
    а) Создаём дерево, создаём итератор, в цикле сдвигаем итератор, проверяя на каждом шаге, что
       мы перешли к определённому элементу.
    б) То же самое, но дерево создаётся вручную.
*/

class Tree;
class TreeIterator;

class Node
{
    Node* left = nullptr,
        * right = nullptr,
        * parent = nullptr;
    friend class Tree;

public:
    Node* getLeft() { return left; }
    const Node* getLeft() const { return left; }
    Node* getRight() { return right; }
    const Node* getRight() const { return right; }
    Node* getParent() { return parent; }
    const Node* getParent() const { return parent; }

    std::string name;
    std::string description;

    Node(const std::string& name_, Node* parent_ = nullptr) :
        left(nullptr), right(nullptr), parent(parent_), name(name_) { }

    Node* findMin()
    {
        Node* node = this;
        while (node->left)
            node = node->left;
        return node;
    }

    Node* findMax()
    {
        Node* node = this;
        while (node->right)
            node = node->right;
        return node;
    }
};

class TreeIterator : public std::iterator<std::input_iterator_tag, Node>
{
    Node* node;

public:
    TreeIterator(Node* node_ = nullptr) : node(node_) {}
    TreeIterator(const TreeIterator& it) : node(it.node) {}

    bool operator == (const TreeIterator& other) const { return node == other.node; }
    bool operator != (const TreeIterator& other) const { return node != other.node; }

    std::string& operator * () { return node->name; }
    const std::string& operator * () const { return node->name; }

    TreeIterator& operator++() {
        if (node->getRight())
        {
            node = node->getRight();
            while (node->getLeft())
            {
                node = node->getLeft();
            }
        }
        else
        {
            Node* temp = node->getParent();
            while (temp && temp->getRight() == node)
            {
                node = temp;
                temp = node->getParent();
            }

            // Если корневой узел дерева не имеет правого потомка и итератор начинается с корневого узла
            if (node->getRight() != temp)
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
        if (node->getLeft())
        {
            node = node->getLeft();
            while (node->getRight())
            {
                node = node->getRight();
            }
        }
        else
        {
            Node* temp = node->getParent();
            while (temp && temp->getLeft() == node)
            {
                node = temp;
                temp = node->getParent();
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

class Tree
{
    Node* root;

    /// Вход: b > a, a - родитель b
    /// Выход: b - родитель a
    void smallTurnLeft(Node*& a, Node* b)
    {
        Node* y = b->right;
        b->right = y->left;
        if (y->left)
            y->left->parent = b;

        y->parent = b->parent;
        if (!b->parent)
            a = y;
        else {
            if (b == b->parent->left)
                b->parent->left = y;
            else
                b->parent->right = y;
        }
        y->left = b;
        b->parent = y;
    }

    /// Вход: b < a, a - родитель b
    /// Выход: b - родитель a
    void smallTurnRight(Node*& a, Node* b)
    {
        Node* y = b->left;
        b->left = y->right;
        if (y->right)
            y->right->parent = b;

        y->parent = b->parent;
        if (!b->parent)
            a = y;
        else {
            if (b == b->parent->right)
                b->parent->right = y;
            else
                b->parent->left = y;
        }
        y->right = b;
        b->parent = y;
    }

    void bigTurnLeft(Node* a, Node* b, Node* c)
    {
        smallTurnRight(b, c);
        smallTurnLeft(a, c);
    }

    void bigTurnRight(Node* a, Node* b, Node* c)
    {
        smallTurnLeft(b, c);
        smallTurnRight(a, c);
    }

    Node* addNode(const std::string& name, Node* node, Node* parent)
    {
        if (!node)
        {
            node = new Node(name, parent);
            return node;
        }

        if (node && name.compare(node->name) > 0) // имя нового элемента длиннее имени корня
        {
            node->right = addNode(name, node->right, node);
            parent = testToBalance(parent);
        }
        else if (node && name.compare(node->name) < 0) // имя нового элемента короче имени корня
        {
            node->left = addNode(name, node->left, node);
            parent = testToBalance(parent);
        }

        return node;
    }

public:
    Node* getRoot() { return root; }
    const Node* getRoot() const { return root; }

    Tree() : root(nullptr) { }

    Node* addNode(const std::string& name)
    {
        if (root == nullptr) // нет элементов
        {
            root = new Node(name); // у корня нет родителей
            return root;
        }
        if (name.compare(root->name) > 0) // имя нового элемента длиннее имени корня
        {
            root->right = addNode(name, root->right, root);
        }
        else if (name.compare(root->name) < 0) // имя нового элемента короче имени корня
        {
            root->left = addNode(name, root->left, root);
        }
    }

    void print()
    {
        if (!root)
            std::cout << "empty RBtree\n";
        else
            print(root);

        std::cout << "\n\n";
    }
    void print(Node* node) const
    {
        if (!node)
            return;
        if (!node->parent)
            std::cout << "\n(" << node->name << ") is root" << std::endl;
        else if (node->parent->left == node)
        {
            std::cout << "\n(" << node->name << ") is " << node->parent->name << "'s " << "left child" << std::endl;
        }
        else
        {
            std::cout << "\n(" << node->name << ") is " << node->parent->name << "'s " << "right child" << std::endl;
        }
        print(node->left);
        print(node->right);
    }

    Node* testToBalance(Node* node)
    {
        int bal_factor = difference(node);
        std::cout << "\nbal_factor = " << bal_factor;
        if (bal_factor > 1)
        {
            if (difference(node->getLeft()) > 0)
            {
                smallTurnLeft(node, node->left);
            }
            else
            {
                smallTurnLeft(node, node->left);
                //smallTurnLeft(node, node->right);
            }
        }
        else if (bal_factor < -1)
        {
            if (difference(node->getRight()) > 0)
            {
                smallTurnRight(node, node->right);
            }
            else
            {
                smallTurnLeft(node, node->right);
                //smallTurnLeft(node, node->right);
            }

        }
        return node;
    }

    int difference(Node* node)
    {
        if (node)
        {
            int l_h = findHeight(node->getLeft());
            int r_h = findHeight(node->getRight());
            return l_h - r_h;
        }

        return 0;
    }

    Node* findNode(const std::string& name)
    {
        Node* node = root;
        while (node)
        {
            auto res = name.compare(node->name);
            if (res == 0)
                return node;
            if (res < 0)
                node = node->left;
            else
                node = node->right;
        }
        return nullptr;
    }

    Node* findMin()
    {
        Node* node = root;
        if (!node)
            return nullptr;
        while (node->left)
            node = node->left;
        return node;
    }

    Node* findMax()
    {
        Node* node = root;
        if (!node)
            return nullptr;
        while (node->right)
            node = node->right;
        return node;
    }

    /// Ищет узел с таким же, или максимально близким справа ("большим") значением name.
    Node* findClosest(const std::string& name)
    {
        Node* node = root;
        while (node)
        {
            auto res = name.compare(node->name);
            if (res == 0)
                return node;
            if (res < 0)
                node = node->left;
            else
                node = node->right;
        }
        return node;
    }
    int findHeight(const Node* node)
    {
        if (node == nullptr)
            return 0;
        int left = findHeight(node->getLeft());
        int right = findHeight(node->getRight());
        return std::max(left, right) + 1;
    }

    void deleteNode(Node* node)
    {
        if (!node)
            return;

        deleteNode(node->left);
        deleteNode(node->right);

        delete node;
        node = nullptr;
    }

    ~Tree()
    {
        deleteNode(root);
    }

    TreeIterator begin() { return this->findMin(); }     /// Возвращает итератор, указывающий на минимальный элемент
    TreeIterator end() { return this->findMax()->getRight(); }       /// Возвращает итератор, указывающий на nullptr Node
};





#include <map>
#include <set>

void testAddNode() {
    Tree* result = new Tree();

    auto abc = result->addNode("Abc");
    /*assert(abc != nullptr);
    assert(abc->name == "Abc");
    assert(abc->description == "");
    assert(abc->getParent() == nullptr);
    assert(abc->getLeft() == nullptr);
    assert(abc->getRight() == nullptr);*/
    result->print();


    auto def = result->addNode("Def");
    /*assert(def != nullptr);
    assert(def->name == "Def");
    assert(def->description == "");
    assert(def->getParent() == abc);
    assert(abc->getRight() == def);*/
    result->print();

    auto ghi = result->addNode("Ghi");
    ghi = result->findNode("Ghi");
    /*assert(ghi != nullptr);
    assert(ghi->name == "Ghi");
    assert(ghi->description == "");
    assert(ghi->getParent() == def);
    assert(ghi->getLeft() == nullptr);
    assert(ghi->getRight() == nullptr);*/
    result->print();

    auto abb = result->addNode("Abb");
    abb = result->findNode("Abb");
    //assert(abb != nullptr);
    //assert(abb->name == "Abb");
    //assert(abb->description == "");
    //assert(abb->getParent() == abc);
    //assert(abb->getLeft() == nullptr);
    //assert(abb->getRight() == nullptr);
    //assert(abc->getParent() == def);
    //assert(abc->getLeft() == abb);
    //assert(abc->getRight() == nullptr);
    result->print();

    auto ab = result->addNode("Ab");
    //assert(ab != nullptr);
    //assert(ab->name == "Ab");
    //assert(ab->description == "");
    //assert(ab->getParent() == abb);
    //assert(ab->getLeft() == nullptr);
    //assert(ab->getRight() == nullptr);
    //assert(abc->getParent() == nullptr);
    //assert(abc->getLeft() == abb);
    //assert(abc->getRight() == def);
    //assert(def->getParent() == abc);
    //assert(def->getLeft() == nullptr);
    //assert(def->getRight() == ghi);
    result->print();

    auto abbbbb = result->addNode("Abbbbb");
    //assert(abbbbb != nullptr);
    //assert(abbbbb->name == "Abbbbb");
    //assert(abbbbb->description == "");
    //assert(abbbbb->getParent() == abb);
    //assert(abbbbb->getLeft() == ab);
    //assert(abbbbb->getRight() == nullptr);
    //assert(abb->getParent() == nullptr);
    //assert(abb->getLeft() == abbbbb);
    //assert(abb->getRight() == abc);
    //assert(abc->getParent() == abb);
    //assert(abc->getLeft() == nullptr);
    //assert(abc->getRight() == def);

    result->print();

    auto ddf = result->addNode("Ddf");
    //assert(ddf != nullptr);
    //assert(ddf->name == "Ddf");
    //assert(ddf->description == "");
    //assert(ddf->getParent() == nullptr);
    //assert(ddf->getLeft() == abc);
    //assert(ddf->getRight() == def);
    //assert(abc->getParent() == ddf);
    //assert(abc->getLeft() == abb);
    //assert(abc->getRight() == nullptr);
    //assert(def->getParent() == ddf);
    //assert(def->getLeft() == nullptr);
    //assert(def->getRight() == ghi);
    result->print();


    std::cout << "\nTest Complite\n";
}

int main()
{
    std::cout << "Test" << std::endl;
    testAddNode();


    return 0;
}
