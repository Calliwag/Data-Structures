#include "mssm.h"
#include "gtest/gtest.h"

template <typename T>
class Deque
{
private:
    T* array;
    int allMem;
    int index;
    int length;

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
    allMem = 10;
    array = new T[10];
    index = 0;
    length = 0;
}

template <typename T>
Deque<T>::~Deque()
{
    delete [] array;
}

template <typename T>
void Deque<T>::pushFront(T val)
{
    index = (index - 1 + allMem) % allMem;
    length++;
    array[index] = val;
    if(length == allMem)
    {
        T* newArray = new T[allMem * 2];
        int newMem = allMem * 2;
        for(int i = 0; i < length; i++)
        {
            newArray[i] = array[(index + i) % allMem];
        }
        delete [] array;
        array = newArray;
        allMem = newMem;
        index = 0;
    }
}

template <typename T>
void Deque<T>::pushBack(T val)
{
    array[(index + length) % allMem] = val;
    length++;
    if(length == allMem)
    {
        T* newArray = new T[allMem * 2];
        int newMem = allMem * 2;
        for(int i = 0; i < length; i++)
        {
            newArray[i] = array[(index + i) % allMem];
        }
        delete [] array;
        array = newArray;
        allMem = newMem;
        index = 0;
    }
}

template <typename T>
T Deque<T>::popFront()
{
    T val = array[index];
    array[index] = T{};
    index = (index + 1) % allMem;
    length--;
    return val;
}

template <typename T>
T Deque<T>::popBack()
{
    T val = array[(index + length - 1) % allMem];
    array[(index + length - 1) % allMem] = T{};
    length--;
    return val;
}

template <typename T>
T Deque<T>::front()
{
    return array[index];
}

template <typename T>
T Deque<T>::back()
{
    return array[(index + length - 1) % allMem];
}

template <typename T>
int Deque<T>::getSize()
{
    return length;
}

template <typename T>
bool Deque<T>::isEmpty()
{
    if(length == 0) return true;
    else return false;
}

TEST(TestDeque, EmptyDequeIsEmpty)
{
    Deque<int> s;
    ASSERT_TRUE(s.isEmpty());
}

TEST(TestDeque, EmptyDequeSizeZero)
{
    Deque<int> s;
    ASSERT_EQ(s.getSize(), 0);
}

TEST(TestDeque, NonEmptyDequeNotEmpty)
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
        s.pushBack(i);
    }
    for(int i = 0; i < 500; i++)
    {
        s.popFront();
    }
    ASSERT_EQ(s.front(), 500);
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
