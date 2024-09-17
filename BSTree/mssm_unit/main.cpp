#include "mssm.h"
#include "gtest/gtest.h"

int nodeNum = 0;
int rotNum = 0;

template <typename T>
class BSTree;

template <typename T>
class Node
{
private:
    T nodeVal;
    Node<T>* left;
    Node<T>* right;
    int height;

    int rHeight();
    int lHeight();
    T getRightMost();
    void updateHeight();
    void balance();
    void rotateRight();
    void rotateLeft();

public:
    Node(Node* _left, Node* _right, T _nodeVal);
    ~Node();
    T getValue();
    int insert(T value);
    void rootRemove(T value, BSTree<T>* tree);
    void remove(T value, Node<T>* parent);
    bool includes(T value);
    vector<T> inOrder();
    vector<T> preOrder();
    vector<T> postOrder();
    int size();

    friend class BSTree<T>;
};

template <typename T>
Node<T>::Node(Node<T>* _left, Node<T>* _right, T _nodeVal)
{
    nodeNum ++;
    left = _left;
    right = _right;
    nodeVal = _nodeVal;
    int lHeight = -1;
    int rHeight = -1;
    if(left) lHeight = left->height;
    if(right) rHeight = right->height;
    height = max(lHeight,rHeight) + 1;
}

template <typename T>
Node<T>::~Node()
{
    nodeNum --;
    delete left;
    delete right;
}

template <typename T>
int Node<T>::insert(T value)
{
    int newHeight = height;
    if(value < nodeVal)
    {
        if(left)
        {
            newHeight = max(left->insert(value) + 1,height);
        }
        else
        {
            left = new Node<T>(nullptr, nullptr, value);
            newHeight = 1;
        }
    }
    else if(value > nodeVal)
    {
        if(right)
        {
            newHeight = max(right->insert(value) + 1,height);
        }
        else
        {
            right = new Node<T>(nullptr, nullptr, value);
            newHeight = 1;
        }
    }
    height = newHeight;
    balance();
    return newHeight;
}

template <typename T>
T Node<T>::getRightMost()
{
    T returns;
    if(right)
    {
        returns = right->getRightMost();
    }
    else
    {
        returns = nodeVal;
    }
    return returns;
}

template <typename T>
int Node<T>::lHeight()
{
    if(left) return left->height;
    return -1;
}

template <typename T>
int Node<T>::rHeight()
{
    if(right) return right->height;
    return -1;
}

template <typename T>
void Node<T>::updateHeight()
{
    height = max(lHeight(),rHeight()) + 1;
}

template <typename T>
void Node<T>::balance()
{
    int balanceFactor = rHeight() - lHeight();
    if(balanceFactor <= -2)
    {
        if(left->rHeight() > left->lHeight()) left->rotateLeft();
        rotateRight();
    }
    else if(balanceFactor >= 2)
    {
        if(right->lHeight() > right->rHeight()) right->rotateRight();
        rotateLeft();
    }
}

template <typename T>
void Node<T>::rotateRight()
{
    rotNum ++;
    Node<T>* llNode = left->left;
    Node<T>* lrNode = left->right;
    Node<T>* rNode = nullptr;
    if(right)
    {
        rNode = new Node<T>(right->left, right->right, right->nodeVal);
        right->right = nullptr;
        right->left = nullptr;
        delete right;
    }
    right = new Node<T>(lrNode, rNode, nodeVal);
    right->updateHeight();

    left->left = nullptr;
    left->right = nullptr;
    delete left;

    nodeVal = left->nodeVal;
    left = llNode;
    updateHeight();
}

template <typename T>
void Node<T>::rotateLeft()
{
    rotNum ++;
    Node<T>* rrNode = right->right;
    Node<T>* rlNode = right->left;
    Node<T>* lNode = nullptr;
    if(left)
    {
        lNode = new Node<T>(left->left, left->right, left->nodeVal);
        left->left = nullptr;
        left->right = nullptr;
        delete left;
    }
    left = new Node<T>(lNode, rlNode, nodeVal);
    left->updateHeight();

    right->left = nullptr;
    right->right = nullptr;
    delete right;

    nodeVal = right->nodeVal;
    right = rrNode;
    updateHeight();
}

template <typename T>
void Node<T>::rootRemove(T value, BSTree<T>* tree)
{
    if(nodeVal == value)
    {
        if(left && right)
        {
            T newValue = left->getRightMost();
            nodeVal = newValue;
            left->remove(newValue, this);
        }
        else if(left)
        {
            Node<T>* oldLeft = left;

            nodeVal = oldLeft->nodeVal;
            left = oldLeft->left;
            right = oldLeft->right;

            oldLeft->right = nullptr;
            oldLeft->left = nullptr;
            delete oldLeft;
            height--;
        }
        else if(right)
        {
            Node<T>* oldRight = right;

            nodeVal = oldRight->nodeVal;
            left = oldRight->left;
            right = oldRight->right;

            oldRight->right = nullptr;
            oldRight->left = nullptr;
            delete oldRight;
            height--;
        }
        else
        {
            tree->root = nullptr;
            delete this;
            return;
        }
    }
    else
    {
        if(left) left->remove(value, this);
        if(right) right->remove(value, this);
    }
    updateHeight();
    balance();
}

template <typename T>
void Node<T>::remove(T value, Node<T>* parent)
{
    int newHeight = height;
    if(nodeVal == value)
    {
        if(left && right)
        {
            T newValue = left->getRightMost();
            nodeVal = newValue;
            left->remove(newValue, this);
        }
        else if(left)
        {
            Node<T>* oldLeft = left;

            nodeVal = oldLeft->nodeVal;
            left = oldLeft->left;
            right = oldLeft->right;

            oldLeft->right = nullptr;
            oldLeft->left = nullptr;
            delete oldLeft;
            height--;
        }
        else if(right)
        {
            Node<T>* oldRight = right;

            nodeVal = oldRight->nodeVal;
            left = oldRight->left;
            right = oldRight->right;

            oldRight->right = nullptr;
            oldRight->left = nullptr;
            delete oldRight;
            height--;
        }
        else
        {
            if(parent->left == this)
            {
                parent->left = nullptr;
            }
            if(parent->right == this)
            {
                parent->right = nullptr;
            }
            delete this;
            return;
        }
    }
    else
    {
        if(left) left->remove(value, this);
        if(right) right->remove(value, this);;
    }
    updateHeight();
    balance();
}

template <typename T>
bool Node<T>::includes(T value)
{
    if(nodeVal == value) return true;
    if(left)
    {
        if(left->includes(value)) return true;
    }
    if(right)
    {
        if(right->includes(value)) return true;
    }
    return false;
}

template <typename T>
vector<T> Node<T>::inOrder()
{
    std::vector<T> list = {};
    if(left)
    {
        std::vector<T> returned = left->inOrder();
        list.insert(std::end(list), std::begin(returned), std::end(returned));
    }
    list.push_back(nodeVal);
    if(right)
    {
        std::vector<T> returned = right->inOrder();
        list.insert(std::end(list), std::begin(returned), std::end(returned));
    }
    return list;
}

template <typename T>
vector<T> Node<T>::preOrder()
{
    std::vector<T> list = {nodeVal};
    if(left)
    {
        std::vector<T> returned = left->preOrder();
        list.insert(std::end(list), std::begin(returned), std::end(returned));
    }
    if(right)
    {
        std::vector<T> returned = right->preOrder();
        list.insert(std::end(list), std::begin(returned), std::end(returned));
    }
    return list;
}

template <typename T>
vector<T> Node<T>::postOrder()
{
    std::vector<T> list = {};
    if(left)
    {
        std::vector<T> returned = left->postOrder();
        list.insert(std::end(list), std::begin(returned), std::end(returned));
    }
    if(right)
    {
        std::vector<T> returned = right->postOrder();
        list.insert(std::end(list), std::begin(returned), std::end(returned));
    }
    list.push_back(nodeVal);
    return list;
}

template <typename T>
int Node<T>::size()
{
    int size = 0;
    if(left) size += left->size();
    if(right) size += right->size();
    size++;
    return size;
}

template <typename T>
class BSTree
{
private:
    Node<T>* root;

public:
    BSTree();
    ~BSTree();
    BSTree (const BSTree<T>&) = delete;
    BSTree<T>& operator= (const BSTree<T>&) = delete;
    void insert(T value);
    void remove(T value);
    bool includes(T value);
    vector<T> inOrder();
    vector<T> preOrder();
    vector<T> postOrder();
    int size();
    bool isEmpty();
    int getHeight();

    friend class Node<T>;
};

template <typename T>
BSTree<T>::BSTree()
{
    root = nullptr;
}

template <typename T>
BSTree<T>::~BSTree()
{
    delete root;
}

template <typename T>
void BSTree<T>::insert(T value)
{
    if(root)
    {
        root->insert(value);
    }
    else
    {
        root = new Node<T>(nullptr, nullptr, value);
    }
}

template <typename T>
void BSTree<T>::remove(T value)
{
    if(root) root->rootRemove(value, this);
}

template <typename T>
bool BSTree<T>::includes(T value)
{
    if(root)
    {
        return root->includes(value);
    }
    return false;
}

template <typename T>
vector<T> BSTree<T>::inOrder()
{
    std::vector<T> list = {};
    if(root)
    {
        list = root->inOrder();
    }
    return list;
}

template <typename T>
vector<T> BSTree<T>::preOrder()
{
    std::vector<T> list = {};
    if(root)
    {
        list = root->preOrder();
    }
    return list;
}

template <typename T>
vector<T> BSTree<T>::postOrder()
{
    std::vector<T> list = {};
    if(root)
    {
        list = root->postOrder();
    }
    return list;
}

template <typename T>
int BSTree<T>::size()
{
    int size = 0;
    if(root)
    {
        size = root->size();
    }
    return size;
}

template <typename T>
bool BSTree<T>::isEmpty()
{
    return size() == 0;
}

template <typename T>
int BSTree<T>::getHeight()
{
    if(root) return root->height;
    return -1;
}

TEST(TestBSTree, HeightTest)
{
    BSTree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(-1);
    tree.insert(0);
    ASSERT_EQ(tree.getHeight(), 3);
}

TEST(TestBSTree, CrashTest)
{
    BSTree<int> tree;
    tree.insert(11);
    tree.insert(3);
    tree.insert(44);
    tree.remove(3);
    tree.insert(1);
    tree.insert(5);
    tree.insert(7);
    tree.remove(5);
    tree.insert(8);
    tree.insert(7);
    tree.insert(6);
    tree.insert(5);
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    tree.remove(44);
    ASSERT_TRUE(true);
}

TEST(TestBSTree, RemoveTest)
{
    BSTree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(-1);
    tree.insert(0);
    tree.remove(1);
    ASSERT_EQ(tree.includes(1), false);
}

TEST(TestBSTree, RemoveRootTest)
{
    BSTree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(-1);
    tree.insert(0);
    tree.remove(2);
    ASSERT_EQ(tree.includes(2), false);
    std::vector<int> expected = {1,0,-1,3};
    ASSERT_EQ(tree.preOrder(), expected);
}

TEST(TestBSTree, RemoveAllTest)
{
    BSTree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.remove(2);
    tree.remove(1);
    tree.remove(3);
    std::vector<int> expected = {};
    ASSERT_EQ(tree.preOrder(), expected);
    ASSERT_TRUE(tree.isEmpty());
}

TEST(TestBSTree, RemoveAllHeightTest)
{
    BSTree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(-1);
    tree.insert(0);
    ASSERT_EQ(tree.getHeight(), 3);
    tree.remove(2);
    ASSERT_EQ(tree.getHeight(), 2);
    tree.remove(-1);
    ASSERT_EQ(tree.getHeight(), 1);
    tree.remove(3);
    ASSERT_EQ(tree.getHeight(), 1);
    tree.remove(1);
    ASSERT_EQ(tree.getHeight(), 0);
    tree.remove(0);
    ASSERT_EQ(tree.getHeight(), -1);
}

TEST(TestBSTree, BalanceTest)
{
    BSTree<int> tree;
    tree.insert(0);
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);
    vector<int> expected = {1,0,3,2,4};
    ASSERT_EQ(tree.preOrder(), expected);
}

TEST(TestBSTree, RemoveBalanceTest)
{
    BSTree<int> tree;
    tree.insert(0);
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    tree.insert(4);

    tree.remove(3);
    tree.remove(4);
    tree.remove(1);
    tree.remove(2);
    tree.remove(0);
    vector<int> expected = {};
    ASSERT_EQ(tree.preOrder(), expected);
}

TEST(TestBSTree, IncludesTest)
{
    BSTree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(-1);
    tree.insert(0);
    ASSERT_EQ(tree.includes(3), true);
    ASSERT_EQ(tree.includes(5), false);
}

TEST(TestBSTree, InOrderTest)
{
    BSTree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(-1);
    tree.insert(0);
    std::vector<int> expected = {-1,0,1,2,3};
    ASSERT_EQ(tree.inOrder(), expected);
}

TEST(TestBSTree, PreOrderTest)
{
    BSTree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(-1);
    tree.insert(0);
    std::vector<int> expected = {2,0,-1,1,3};
    ASSERT_EQ(tree.preOrder(), expected);
}

TEST(TestBSTree, PostOrderTest)
{
    BSTree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(-1);
    tree.insert(0);
    std::vector<int> expected = {-1,1,0,3,2};
    ASSERT_EQ(tree.postOrder(), expected);
}

TEST(TestBSTree, SizeTest)
{
    BSTree<int> tree;
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(-1);
    tree.insert(0);
    tree.remove(1);
    ASSERT_EQ(tree.size(), 4);
}

TEST(TestBSTree, IsEmptyTest)
{
    BSTree<int> tree;
    ASSERT_TRUE(tree.isEmpty());
    tree.insert(2);
    tree.insert(1);
    tree.insert(3);
    tree.insert(-1);
    tree.insert(0);
    tree.remove(1);
    ASSERT_FALSE(tree.isEmpty());
}

int main()
{
    ::testing::InitGoogleTest();
    int res = RUN_ALL_TESTS();;

    cout << nodeNum << endl << rotNum << endl;

    return res;
}
