#include "mssm.h"
#include "gtest/gtest.h"

template <typename T>
class Deque
{
private:
    T* array;
    int arraySize;
    int front;
    int back;

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
Deque::Deque()
{

}

template <typename T>
Deque::~Deque()
{

}

template <typename T>
void Deque::PushFront(T val)
{
    if(front % arraySize == (back + 1) % arraySize)
    {
        T* newArray = T[arraySize * 2];
        for(int i = 0; i < arraySize; i++)
        {
            newArray[i] = array[(front + i) % arraySize];
        }
        delete [] array;
        array = newArray;
        front = 0;
        back = arraySize - 1;
        arraySize *= 2;
    }
    array[back + 1] = val;
    back = (back + 1) % arraySize;
}

template <typename T>
void Deque::PushBack(T val)
{

}

template <typename T>
T popFront()
{

}

template <typename T>
T popBack()
{

}

template <typename T>
T front()
{

}

template <typename T>
T back()
{

}

template <typename T>
int getSize()
{

}

template <typename T>
bool isEmpty()
{

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

TEST(TestDeque, PushAndFrontBackGivesCorrectValue)
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
    ASSERT_EQ(s.top(), 2);
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
    ASSERT_EQ(s.top(), 500);
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
    ASSERT_EQ(s.top(), "500");
}

int main()
{
    ::testing::InitGoogleTest();
    int res = RUN_ALL_TESTS();;

    return res;
}
