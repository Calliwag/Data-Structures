#include "mssm.h"
#include "gtest/gtest.h"

template <typename T>
class PriorityQueue
{
private:
    T treeArr;
    int allMem;
    int size;

public:
    PriorityQueue();
    void insert(T val);
    void parentSwap(int index);
};

template <typename T>
PriorityQueue<T>::PriorityQueue()
{
    treeArr = new T[1];
    allMem = 1;
    size = 0;
}

template <typename T>
void PriorityQueue<T>::insert(T val)
{
    if(size == allocMem)
    {
        T tempArr = treeArr;
        delete [] treeArr;
        treeArr = new T[allMem * 2];
        for(int i = 0; i < allMem; i++)
        {
            treeArr[i] = tempArr[i];
        }
        delete [] tempArr;
        allMem *= 2;
    }
    treeArr[size] = val;
    parentSwap(size);
    size++;
}

template <typename T>
void PriorityQueue<T>::parentSwap(T val)
{
    if()
}

TEST(Test, Name)
{

}

int main()
{
    ::testing::InitGoogleTest();
    int res = RUN_ALL_TESTS();;

    return res;
}
