#include <cassert>
#include <iterator>
//#include <iostream>
//#include <string>
//
/////
///// Домашнее задание:
/////
///// 1.  Добавить findMin() и findMax() в классе Node, аналогичные таковым в Tree; 
/////     они должны искать в поддереве, корнем которого является текущий узел.            +
/////
///// 2.  Реализовать малый правый поворот, а также большие левый и правый повороты
/////     в классе Tree, по аналогии с малым левым поворотом.                              +
/////
///// 3.  Реализовать префиксный оператор «++» для итератора.                              +
/////
///// 4.  Реализовать Tree::findClosest() и Tree::deleteNode().                            +
/////
///// 5.  Реализовать юнит-тесты на все публичные методы классов Tree и TreeIterator,
/////     кроме тривиальных. Прогонять эти тесты в функции main().
/////
//
///**
//1. Добавление.
//    а) (интерфейсный способ) Создаём дерево, вызываем addNode(), проверяем:
//        * что элемент добавился?
//        * что элемент добавился по соседству с определёнными другими элементами?
//        * сравнить дерево целиком с эталоном?
//    б) (инвазивный) Конструируем объекты Node и Tree вручную, затем вызываем addNode(), проверяем (то же).
//2. Удаление.
//    а) Создаём дерево, вызываем removeNode(), проверяем:
//        * что элемента в дереве больше нет?
//        * что бывшие соседи элемента получили определённое новое состояние?
//        * сравнить дерево целиком с эталоном?
//    б) Конструируем объекты Node и Tree вручную, затем вызываем removeNode(), проверяем (то же).
//3. Проход по дереву.
//    а) Создаём дерево, создаём итератор, в цикле сдвигаем итератор, проверяя на каждом шаге, что
//       мы перешли к определённому элементу.
//    б) То же самое, но дерево создаётся вручную.
//*/
//
class Tree;
class TreeIterator;

#include <cassert>
#include <iostream>
#include <string>

class Tree;

class Node
{
    Node* left, * right, * parent;
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

    Node(const std::string& name_, Node* parent_ = nullptr)
        : left(nullptr),
        right(nullptr),
        parent(parent_),
        name(name_)
    { }
    Node(const Node*& newNode)
    {
        this->parent = newNode->parent;
        this->left = newNode->left;
        this->right = newNode->right;
        this->name = newNode->name;
        this->description = newNode->description;
    }

    Node* findMin() {
        Node* temp = this;
        while (temp->left)
            temp = temp->left;
        return temp;
    }

    Node* findMax() {
        Node* temp = this;
        while (temp->right)
            temp = temp->right;
        return temp;
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


class Tree {
    Node* root;

    void smallTurnLeft(Node* a, Node* b)
    {
        if (a->parent)
            if (a->parent->right && a->parent->right == a)
                a->parent->right = b;
            else
                a->parent->left = b;
        else
            root = b;
        b->parent = a->parent;
        a->parent = b;
        if (b->left)
        {
            b->left->parent = a;
            a->right = b->left;
        }
        else
            a->right = nullptr;
        b->left = a;
    }

    void smallTurnRight(Node* a, Node* b)
    {
        if (a->parent)
            if (a->parent->left && a->parent->left == a)
                a->parent->left = b;
            else
                a->parent->right = b;
        else
            root = b;
        b->parent = a->parent;
        a->parent = b;
        if (b->right)
        {
            b->right->parent = a;
            a->left = b->right;
        }
        else
            a->left = nullptr;
        b->right = a;
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

    void deleteNode(Node* node)
    {
        if (!node)
            return;

        deleteNode(node->left);
        deleteNode(node->right);

        delete node;
        node = nullptr;
    }

    Node* findClosest(const std::string& name)
    {
        Node* node = root;
        Node* res = nullptr;
        while (node)
        {
            res = node;
            auto res = name.compare(node->name);
            if (res == 0)
                return node;
            if (res < 0)
                node = node->left;
            else
                node = node->right;
        }
        return res;
    }
public:
    Node* getRoot() { return root; }
    const Node* getRoot() const { return root; }

    Tree() : root(nullptr) { }

    ~Tree()
    {
        deleteNode(root);
    }

    Node* addNode(Node* newNode = nullptr)
    {
        auto tempResNode = findNode(newNode->name);
        if (tempResNode != nullptr) // дубликат
        {
            return tempResNode;
        }
        else if (!newNode) //кто-то решил что-то проверить
        {
            return nullptr;
        }
        else // Node уже живой и существует
        {
            if (root == nullptr)
            {
                root = newNode;
                return root;
            }

            Node* closest = findClosest(newNode->name);

            if (newNode->name.compare(closest->name) < 0)
            {
                closest->left = newNode;
                newNode->parent = closest;
            }
            else if (newNode->name.compare(closest->name) > 0)
            {
                closest->right = newNode;
                newNode->parent = closest;
            }

            if (closest == root)
                return newNode;

            if (closest->parent->left == closest)
            {
                if (closest->parent->right == nullptr)
                {
                    if (newNode->name.compare(closest->name) < 0)
                        smallTurnRight(closest->parent, closest);
                    else
                        bigTurnRight(closest->parent, closest, newNode);
                }
            }
            else
            {
                if (closest->parent->left == nullptr)
                {
                    if (newNode->name.compare(closest->name) < 0)
                        bigTurnLeft(closest->parent, closest, newNode);
                    else
                        smallTurnLeft(closest->parent, closest);
                }
            }

            return newNode;
        }

    }

    Node* addNode(const std::string& name)
    {
        if (root == nullptr)
        {
            Node* newNode = new Node(name, nullptr);
            root = newNode;
            return root;
        }

        Node* closest = findClosest(name);
        if (closest && closest->name == name)
            return nullptr;

        Node* newNode = new Node(name, closest);

        if (name.compare(closest->name) < 0)
        {
            closest->left = newNode;
            newNode->parent = closest;
        }
        else if (name.compare(closest->name) > 0)
        {
            closest->right = newNode;
            newNode->parent = closest;
        }

        if (closest == root)
            return newNode;

        if (closest->parent->left == closest)
        {
            if (closest->parent->right == nullptr)
            {
                if (name.compare(closest->name) < 0)
                    smallTurnRight(closest->parent, closest);
                else
                    bigTurnRight(closest->parent, closest, newNode);
            }
        }
        else
        {
            if (closest->parent->left == nullptr)
            {
                if (name.compare(closest->name) < 0)
                    bigTurnLeft(closest->parent, closest, newNode);
                else
                    smallTurnLeft(closest->parent, closest);
            }
        }

        return newNode;

    }

    Node* findNode(const std::string& name)
    {
        auto node = root;
        while (node)
        {
            if (name.compare(node->name) == 0)
                return node;
            if (name.compare(node->name) < 0)
                node = node->left;
            else
                node = node->right;
        }
        return nullptr;
    }

    Node* findMin(Node* n)
    {
        Node* node = n;
        if (!node)
            return nullptr;
        while (node->left)
            node = node->left;
        return node;
    }

    Node* findMax(Node* n)
    {
        Node* node = n;
        if (!node)
            return nullptr;
        while (node->right)
            node = node->right;
        return node;
    }

    Node* removeNode(const std::string& name)
    {
        Node* parent;
        Node* node = root;

        if (root == nullptr)
            return nullptr;
        else
        {
            while (name.compare(node->name) != 0)
            {
                if (name.compare(node->name) < 0)
                    if (node->left != nullptr)
                        node = node->left;
                    else
                        return nullptr;
                else
                    if (node->right != nullptr)
                        node = node->right;
                    else
                        return nullptr;
            }

            parent = node->parent;

            if (node->left == nullptr && node->right == nullptr)
            {
                if (parent->right == node)
                    parent->right = nullptr;
                else
                    parent->left = nullptr;
                node->parent = nullptr;
            }

            else if (node->left == nullptr)
            {
                if (parent->right = node)
                    parent->right = node->right;
                else
                    parent->left = node->right;

                node->right->parent = parent;
                node->parent = nullptr;
                node->right = nullptr;
            }

            else if (node->right == nullptr)
            {
                if (parent->right = node)
                    parent->right = node->left;
                else
                    parent->left = node->left;

                node->left->parent = parent;
                node->parent = nullptr;
                node->left = nullptr;
            }

            else
            {
                Node* min = findMin(node->right);
                node->name = min->name;
                parent = min->parent;
                if (parent == node)
                    parent->right = nullptr;
                else
                    parent->left = nullptr;
                min->parent = nullptr;
            }
        }
        return node;
    }

    TreeIterator begin() { return this->root->findMin(); }                 /// Возвращает итератор, указывающий на минимальный элемент
    TreeIterator end() { return this->root->findMax(); }                   /// Возвращает итератор, указывающий на последний Node
};

void testAddNode() {
    Tree* result = new Tree();

    auto abc = result->addNode("Abc");
    assert(abc != nullptr);
    assert(abc->name == "Abc");
    assert(abc->description == "");
    assert(abc->getParent() == nullptr);
    assert(abc->getLeft() == nullptr);
    assert(abc->getRight() == nullptr);


    auto def = result->addNode("Def");
    assert(def != nullptr);
    assert(def->name == "Def");
    assert(def->description == "");
    assert(def->getParent() == abc);
    assert(abc->getRight() == def);

    auto ghi = result->addNode("Ghi");
    ghi = result->findNode("Ghi");
    assert(ghi != nullptr);
    assert(ghi->name == "Ghi");
    assert(ghi->description == "");
    assert(ghi->getParent() == def);
    assert(ghi->getLeft() == nullptr);
    assert(ghi->getRight() == nullptr);

    auto abb = result->addNode("Abb");
    abb = result->findNode("Abb");
    assert(abb != nullptr);
    assert(abb->name == "Abb");
    assert(abb->description == "");
    assert(abb->getParent() == abc);
    assert(abb->getLeft() == nullptr);
    assert(abb->getRight() == nullptr);
    assert(abc->getParent() == def);
    assert(abc->getLeft() == abb);
    assert(abc->getRight() == nullptr);

    auto ab = result->addNode("Ab");
    ab = result->findNode("Ab");
    assert(ab != nullptr);
    assert(ab->name == "Ab");
    assert(ab->description == "");
    assert(ab->getParent() == abb);
    assert(ab->getLeft() == nullptr);
    assert(ab->getRight() == nullptr);
    assert(abc->getParent() == abb);
    assert(abc->getLeft() == nullptr);
    assert(abc->getRight() == nullptr);
    assert(def->getParent() == nullptr);
    assert(def->getLeft() == abb);
    assert(def->getRight() == ghi);

    auto it = result->removeNode("Ab");
    it = result->findNode("Abb");
    assert(it != nullptr);
    assert(it->name == "Abb");
    assert(it->description == "");
    assert(it->getParent() == def);
    assert(it->getLeft() == nullptr);
    assert(it->getRight() == abc);
    assert(abc->getParent() == it);
    assert(abc->getLeft() == nullptr);
    assert(abc->getRight() == nullptr);


    auto min = result->findMin(result->getRoot());
    assert(min->name == *result->begin());

    auto search_node = result->findNode("Abc");
    assert(search_node == abc);

    Node* NodeTest = new Node("Test");
    auto NodeTest2 = new Node("TZest");
    Tree* Tree2 = new Tree();
    auto res = Tree2->addNode(NodeTest);
    assert(res != nullptr);
    assert(res->name == "Test");
    assert(res->getParent() == nullptr);
    assert(res->getRight() == nullptr);
    assert(res->getLeft() == nullptr);

    auto res2 = Tree2->addNode(NodeTest2);
    assert(res2 != nullptr);
    assert(res2->name == "TZest");
    assert(res2->getParent() == res);
    assert(res2->getRight() == nullptr);
    assert(res2->getLeft() == nullptr);
    assert(res->getLeft() == res2);
    assert(res->getRight() == nullptr);

    std::cout << "\nTest Complite\n";
}

void testIterator()
{
    Tree* ItTree = new Tree();
    auto a = ItTree->addNode("Abc");
    auto b = ItTree->addNode("Def");
    auto c = ItTree->addNode("Ghi");
    auto d = ItTree->addNode("AAb");
    TreeIterator it1(ItTree->begin());


    assert(it1 != nullptr);
    assert(*it1 == ItTree->findMin(ItTree->getRoot())->name);
    ++it1;
    assert(*it1 == a->name);
    ++it1;
    assert(*it1 == b->name);
    ++it1;
    assert(*it1 == c->name);
    --it1;
    assert(*it1 == b->name);
    --it1;
    assert(*it1 == a->name);
    --it1;
    assert(*it1 == d->name);
    --it1;
    assert(it1 == nullptr);

    it1 = ItTree->end();
    assert(it1 == c);
    it1--;
    assert(it1 == b);
    it1--;
    assert(it1 == a);
    it1--;
    assert(it1 == d);
    it1--;
    assert(it1 == nullptr);
}


int main()
{
    std::cerr << "Test" << std::endl;
    testAddNode();
    testIterator();
    return 0;
}
