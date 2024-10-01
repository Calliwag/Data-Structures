#include "mssm.h"
#include "gtest/gtest.h"

template <typename T>
class PriorityQueue
{
private:
    // Vars
    T* treeArr;
    int allMem;
    int _size;

    //Funcs
    int parent(int index);
    int child1(int index);
    int child2(int index);
    void parentSwap(int index);
    void childSwap(int index);

public:
    PriorityQueue();
    void insert(T val);
    T remove();
    bool isEmpty();
    int size();

};

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
    treeArr = new T[1];
    allMem = 1;
    _size = 0;
}

template <typename T>
int PriorityQueue<T>::parent(int index)
{
    return (index - 1) / 2;
}

template <typename T>
int PriorityQueue<T>::child1(int index)
{
    return index * 2 + 1;
}

template <typename T>
int PriorityQueue<T>::child2(int index)
{
    return index * 2 + 2;
}

template <typename T>
void PriorityQueue<T>::insert(T val)
{
    if(_size == allMem)
    {
        T* tempArr = treeArr;
        treeArr = new T[allMem * 2];
        for(int i = 0; i < allMem; i++)
        {
            treeArr[i] = tempArr[i];
        }
        delete [] tempArr;
        allMem *= 2;
    }
    treeArr[_size] = val;
    parentSwap(_size);
    _size++;
}

template <typename T>
T PriorityQueue<T>::remove()
{
    T val = treeArr[0];
    treeArr[0] = treeArr[_size - 1];
    childSwap(0);
    _size--;
    return val;
}

template <typename T>
bool PriorityQueue<T>::isEmpty()
{
    return _size == 0;
}

template <typename T>
int PriorityQueue<T>::size()
{
    return _size;
}

template <typename T>
void PriorityQueue<T>::parentSwap(int index)
{
    if(treeArr[parent(index)] < treeArr[index])
    {
        swap(treeArr[parent(index)],treeArr[index]);
        if(parent(index) > 0) parentSwap(parent(index));
    }
}

template <typename T>
void PriorityQueue<T>::childSwap(int index)
{
    bool hasChild1 = (child1(index) < _size);
    bool hasChild2 = (child2(index) < _size);
    if(hasChild1 && hasChild2)
    {
        T child1Val = treeArr[child1(index)];
        T child2Val = treeArr[child2(index)];
        if(child1Val > child2Val && child1Val > treeArr[index]) swap(treeArr[child1(index)],treeArr[index]);
        else if(child2Val > treeArr[index]) swap(treeArr[child2(index)],treeArr[index]);
    }
    else if(hasChild1)
    {
        T child1Val = treeArr[child1(index)];
        if(child1Val > treeArr[index]) swap(treeArr[child1(index)], treeArr[index]);
    }
    else if(hasChild2)
    {
        T child2Val = treeArr[child2(index)];
        if(child2Val > treeArr[index]) swap(treeArr[child2(index)], treeArr[index]);
    }
}

TEST(TestPQ, InsertTest)
{
    PriorityQueue<int> test;
    test.insert(1);
    test.insert(2);
    test.insert(0);
}

TEST(TestPQ, RemoveTest)
{
    PriorityQueue<int> test;
    test.insert(1);
    test.insert(2);
    test.insert(0);
    vector<int> list = {};
    for(int i = 0; i < 3; i++)
    {
        list.push_back(test.remove());
    }
    vector<int> expected = {2,1,0};
    ASSERT_EQ(list,expected);
}

TEST(TestPQ, EmptyTest)
{
    PriorityQueue<int> test;
    ASSERT_TRUE(test.isEmpty());
    test.insert(1);
    test.insert(2);
    test.insert(0);
    for(int i = 0; i < 2; i++)
    {
        test.remove();
    }
    ASSERT_FALSE(test.isEmpty());
    test.remove();
    ASSERT_TRUE(test.isEmpty());
}

TEST(TestPQ, SizeTest)
{
    PriorityQueue<int> test;
    ASSERT_EQ(test.size(), 0);
    test.insert(1);
    test.insert(2);
    test.insert(0);
    for(int i = 0; i < 2; i++)
    {
        test.remove();
    }
    ASSERT_EQ(test.size(), 1);
    test.remove();
    ASSERT_EQ(test.size(), 0);
}

int main()
{
    ::testing::InitGoogleTest();
    int res = RUN_ALL_TESTS();;

    return res;
}
