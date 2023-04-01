#include <cassert>
#include <iostream>
#include <string>

///
/// Äîìàøíåå çàäàíèå:
///
/// 1.  Äîáàâèòü findMin() è findMax() â êëàññå Node, àíàëîãè÷íûå òàêîâûì â Tree;
///     îíè äîëæíû èñêàòü â ïîääåðåâå, êîðíåì êîòîðîãî ÿâëÿåòñÿ òåêóùèé óçåë.
///
/// 2.  Ðåàëèçîâàòü ìàëûé ïðàâûé ïîâîðîò, à òàêæå áîëüøèå ëåâûé è ïðàâûé ïîâîðîòû
///     â êëàññå Tree, ïî àíàëîãèè ñ ìàëûì ëåâûì ïîâîðîòîì.
///
/// 3.  Ðåàëèçîâàòü ïðåôèêñíûé îïåðàòîð «++» äëÿ èòåðàòîðà.
///
/// 4.  Ðåàëèçîâàòü Tree::findClosest() è Tree::deleteNode().
///
/// 5.  Ðåàëèçîâàòü þíèò-òåñòû íà âñå ïóáëè÷íûå ìåòîäû êëàññîâ Tree è TreeIterator,
///     êðîìå òðèâèàëüíûõ. Ïðîãîíÿòü ýòè òåñòû â ôóíêöèè main().
///

/**
1. Äîáàâëåíèå.
    à) (èíòåðôåéñíûé ñïîñîá) Ñîçäà¸ì äåðåâî, âûçûâàåì addNode(), ïðîâåðÿåì:
        * ÷òî ýëåìåíò äîáàâèëñÿ?
        * ÷òî ýëåìåíò äîáàâèëñÿ ïî ñîñåäñòâó ñ îïðåäåë¸ííûìè äðóãèìè ýëåìåíòàìè?
        * ñðàâíèòü äåðåâî öåëèêîì ñ ýòàëîíîì?
    á) (èíâàçèâíûé) Êîíñòðóèðóåì îáúåêòû Node è Tree âðó÷íóþ, çàòåì âûçûâàåì addNode(), ïðîâåðÿåì (òî æå).
2. Óäàëåíèå.
    à) Ñîçäà¸ì äåðåâî, âûçûâàåì removeNode(), ïðîâåðÿåì:
        * ÷òî ýëåìåíòà â äåðåâå áîëüøå íåò?
        * ÷òî áûâøèå ñîñåäè ýëåìåíòà ïîëó÷èëè îïðåäåë¸ííîå íîâîå ñîñòîÿíèå?
        * ñðàâíèòü äåðåâî öåëèêîì ñ ýòàëîíîì?
    á) Êîíñòðóèðóåì îáúåêòû Node è Tree âðó÷íóþ, çàòåì âûçûâàåì removeNode(), ïðîâåðÿåì (òî æå).
3. Ïðîõîä ïî äåðåâó.
    à) Ñîçäà¸ì äåðåâî, ñîçäà¸ì èòåðàòîð, â öèêëå ñäâèãàåì èòåðàòîð, ïðîâåðÿÿ íà êàæäîì øàãå, ÷òî
       ìû ïåðåøëè ê îïðåäåë¸ííîìó ýëåìåíòó.
    á) Òî æå ñàìîå, íî äåðåâî ñîçäà¸òñÿ âðó÷íóþ.
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

            // Åñëè êîðíåâîé óçåë äåðåâà íå èìååò ïðàâîãî ïîòîìêà è èòåðàòîð íà÷èíàåòñÿ ñ êîðíåâîãî óçëà
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

    /// Âõîä: b > a, a - ðîäèòåëü b
    /// Âûõîä: b - ðîäèòåëü a
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

    /// Âõîä: b < a, a - ðîäèòåëü b
    /// Âûõîä: b - ðîäèòåëü a
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

        if (node && name.compare(node->name) > 0) // èìÿ íîâîãî ýëåìåíòà äëèííåå èìåíè êîðíÿ
        {
            node->right = addNode(name, node->right, node);
            std::cout << "\naddNode(Node*, name) right = " << name;
            parent = testToBalance(parent);
        }
        else if (node && name.compare(node->name) < 0) // èìÿ íîâîãî ýëåìåíòà êîðî÷å èìåíè êîðíÿ
        {
            node->left = addNode(name, node->left, node);
            std::cout << "\naddNode(Node*, name) left = " << name;
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
        if (root == nullptr) // íåò ýëåìåíòîâ
        {
            root = new Node(name); // ó êîðíÿ íåò ðîäèòåëåé
            return root;
        }
        if (name.compare(root->name) > 0) // èìÿ íîâîãî ýëåìåíòà äëèííåå èìåíè êîðíÿ
        {
            root->right = addNode(name, root->right, root);
        }
        else if (name.compare(root->name) < 0) // èìÿ íîâîãî ýëåìåíòà êîðî÷å èìåíè êîðíÿ
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
                bigTurnLeft(node->right, node, node->right->left);
                //smallTurnRight(node, node->right);
                //smallTurnLeft(node->parent, node);
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
                bigTurnRight(node->left, node, node->left->right);
                //smallTurnRight(b, c);
                //smallTurnLeft(a, c);
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

    /// Èùåò óçåë ñ òàêèì æå, èëè ìàêñèìàëüíî áëèçêèì ñïðàâà ("áîëüøèì") çíà÷åíèåì name.
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

    TreeIterator begin() { return this->findMin(); }     /// Âîçâðàùàåò èòåðàòîð, óêàçûâàþùèé íà ìèíèìàëüíûé ýëåìåíò
    TreeIterator end() { return this->findMax()->getRight(); }       /// Âîçâðàùàåò èòåðàòîð, óêàçûâàþùèé íà nullptr Node
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
    assert(abc->getLeft() == def);*/
    result->print();

    auto ghi = result->addNode("Ghi");
    /*assert(ghi != nullptr);
    assert(ghi->name == "Ghi");
    assert(ghi->description == "");
    assert(ghi->getParent() == def);
    assert(ghi->getLeft() == nullptr);
    assert(ghi->getRight() == nullptr);*/
    result->print();

    auto abb = result->addNode("Abb");
    /*assert(abb != nullptr);
    assert(abb->name == "Abb");
    assert(abb->description == "");
    assert(abb->getParent() == abc);
    assert(abb->getLeft() == nullptr);
    assert(abb->getRight() == nullptr);
    assert(abc->getParent() == def);
    assert(abc->getLeft() == abb);
    assert(abc->getRight() == nullptr);*/
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