#include "mssm.h"
#include "gtest/gtest.h"

template <typename T>
class Deque
{
private:
    T* array;
    int arraySize;
    int frontIndex;
    int backIndex;

public:
    Deque();
    ~Deque();
    void pushFront(T val);
    void pushBack(T val);
    T popFront();
    T popBack();
    T front();
    T back();
    int getSize();
    bool isEmpty();
};

template <typename T>
Deque<T>::Deque()
{
    arraySize = 10;
    array = new T[10];
    frontIndex = 0;
    backIndex = 1;
}

template <typename T>
Deque<T>::~Deque()
{
    delete [] array;
}

template <typename T>
void Deque<T>::pushFront(T val)
{
    if(frontIndex % arraySize == (backIndex + 1) % arraySize)
    {
        T* newArray = new T[arraySize * 2];
        for(int i = 0; i < arraySize; i++)
        {
            newArray[i] = array[(frontIndex + i) % arraySize];
        }
        delete [] array;
        array = newArray;
        frontIndex = 0;
        backIndex = arraySize - 1;
        arraySize *= 2;
    }
    array[frontIndex] = val;
    frontIndex = (frontIndex - 1 + arraySize) % arraySize;
}

template <typename T>
void Deque<T>::pushBack(T val)
{
    if(frontIndex % arraySize == (backIndex + 1) % arraySize)
    {
        T* newArray = new T[arraySize * 2];
        for(int i = 0; i < arraySize; i++)
        {
            newArray[i] = array[(frontIndex + i + 1) % arraySize];
        }
        delete [] array;
        array = newArray;
        frontIndex = 0;
        backIndex = arraySize - 1;
        arraySize *= 2;
    }
    array[backIndex] = val;
    backIndex = (backIndex + 1 + arraySize) % arraySize;
}

template <typename T>
T Deque<T>::popFront()
{
    T val = array[frontIndex];
    array[frontIndex] = T{};
    frontIndex = (frontIndex + 1 + arraySize) % arraySize;
    return val;
}

template <typename T>
T Deque<T>::popBack()
{
    T val = array[backIndex];
    array[backIndex] = T{};
    frontIndex = (frontIndex - 1 + arraySize) % arraySize;
    return val;
}

template <typename T>
T Deque<T>::front()
{
    return array[frontIndex + 1];
}

template <typename T>
T Deque<T>::back()
{
    return array[backIndex - 1 + arraySize];
}

template <typename T>
int Deque<T>::getSize()
{
    return (backIndex - frontIndex + arraySize) % arraySize;
}

template <typename T>
bool Deque<T>::isEmpty()
{
    if(frontIndex == backIndex)
    {
        return true;
    }
    else
    {
        return false;
    }
}

TEST(TestDeque, EmptyStackIsEmpty)
{
    Deque<int> s;
    ASSERT_TRUE(s.isEmpty());
}

TEST(TestDeque, EmptyStackSizeZero)
{
    Deque<int> s;
    ASSERT_EQ(s.getSize(), 0);
}

TEST(TestDeque, NonEmptyStackNotEmpty)
{
    Deque<int> s;
    s.pushBack(1);
    ASSERT_FALSE(s.isEmpty());
}

TEST(TestDeque, Push1GivesSize1)
{
    Deque<int> s;
    s.pushBack(1);
    ASSERT_EQ(s.getSize(),1);
}

TEST(TestDeque, PushFrontBackGivesCorrectValue)
{
    Deque<int> s;
    s.pushBack(1);
    ASSERT_EQ(1, s.back());
    s.pushFront(-1);
    ASSERT_EQ(-1, s.front());
    s.pushBack(100);
    ASSERT_EQ(100, s.back());
}

TEST(TestDeque, PushAndPopGivesCorrectSize)
{
    Deque<int> s;
    s.pushFront(1);
    s.pushBack(2);
    s.popFront();
    ASSERT_EQ(s.getSize(), 1);
}

TEST(TestDeque, PushAndPopGivesCorrectValue)
{
    Deque<int> s;
    s.pushFront(1);
    s.pushBack(2);
    s.popFront();
    ASSERT_EQ(s.front(), 2);
}

TEST(TestDeque, Push1000GivesCorrectSize)
{
    Deque<int> s;
    for(int i = 0; i < 1000; i++)
    {
        s.pushFront(i);
    }
    ASSERT_EQ(s.getSize(), 1000);
}

TEST(TestDeque, Push1000Pop500GivesCorrectValue)
{
    Deque<int> s;
    for(int i = 0; i < 1000; i++)
    {
        s.pushFront(i);
    }
    for(int i = 0; i < 500; i++)
    {
        s.popBack();
    }
    ASSERT_EQ(s.back(), 500);
}

TEST(TestDeque, Push1000Pop500GivesCorrectString)
{
    Deque<string> s;
    for(int i = 0; i < 1000; i++)
    {
        s.pushFront(to_string(i));
    }
    for(int i = 0; i < 500; i++)
    {
        s.popBack();
    }
    ASSERT_EQ(s.back(), "500");
}

int main()
{
    ::testing::InitGoogleTest();
    int res = RUN_ALL_TESTS();;

    return res;
}
