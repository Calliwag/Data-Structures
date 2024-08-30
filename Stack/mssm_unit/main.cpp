#include "mssm.h"
#include "gtest/gtest.h"

template <typename T>
class Stack
{
private:
    T* data;
    int size;
    int allocatedMemory;
    int memoryAllocateSize = 10;

public:
    Stack();
    ~Stack();
    void push(T val);
    T pop();
    T top();
    int getSize();
    bool isEmpty();
};

template <typename T>
Stack<T>::Stack()
{
    data = new T[memoryAllocateSize];
    allocatedMemory = memoryAllocateSize;
    size = 0;
    println("Constructor called");
}

template <typename T>
Stack<T>::~Stack()
{
    delete [] data;
    println("Destructor called");
}

template <typename T>
void Stack<T>::push(T val)
{
    if(size >= allocatedMemory)
    {
        allocatedMemory += memoryAllocateSize;
        T* newData = new T[allocatedMemory];
        for(int i = 0; i < size; i++)
        {
            newData[i] = data[i];
        }
        delete [] data;
        data = newData;
    }

    data[size] = val;
    size++;
}

template <typename T>
T Stack<T>::pop()
{
    if(size <= allocatedMemory - memoryAllocateSize)
    {
        allocatedMemory -= memoryAllocateSize;
        T* newData = new T[allocatedMemory];
        for(int i = 0; i < size; i++)
        {
            newData[i] = data[i];
        }
        delete [] data;
        data = newData;
    }

    T val = data[size - 1];
    data[size - 1] = T{};
    size--;
    return val;
}

template <typename T>
T Stack<T>::top()
{
    T val = data[size - 1];
    return val;
}

template <typename T>
int Stack<T>::getSize()
{
    return size;
}

template <typename T>
bool Stack<T>::isEmpty()
{
    if(size == 0)
    {
        return true;
    }
    return false;
}

TEST(TestStack, EmptyStackIsEmpty)
{
    Stack<int> s;
    ASSERT_TRUE(s.isEmpty());
}

TEST(TestStack, EmptyStackSizeZero)
{
    Stack<int> s;
    ASSERT_EQ(s.getSize(), 0);
}

TEST(TestStack, NonEmptyStackNotEmpty)
{
    Stack<int> s;
    s.push(1);
    ASSERT_FALSE(s.isEmpty());
}

TEST(TestStack, Push1GivesSize1)
{
    Stack<int> s;
    s.push(1);
    ASSERT_EQ(s.getSize(),1);
}

TEST(TestStack, PushAndTopGivesCorrectValue)
{
    Stack<int> s;
    s.push(1);
    ASSERT_EQ(1, s.top());
    s.push(-1);
    ASSERT_EQ(-1, s.top());
    s.push(100);
    ASSERT_EQ(100, s.top());
}

TEST(TestStack, PushAndPopGivesCorrectSize)
{
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.pop();
    ASSERT_EQ(s.getSize(), 1);
}

TEST(TestStack, PushAndPopGivesCorrectValue)
{
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.pop();
    ASSERT_EQ(s.top(), 1);
}

TEST(TestStack, Push1000GivesCorrectSize)
{
    Stack<int> s;
    for(int i = 0; i < 1000; i++)
    {
        s.push(i);
    }
    ASSERT_EQ(s.getSize(), 1000);
}

TEST(TestStack, Push1000Pop500GivesCorrectValue)
{
    Stack<int> s;
    for(int i = 0; i < 1000; i++)
    {
        s.push(i);
    }
    for(int i = 0; i < 500; i++)
    {
        s.pop();
    }
    ASSERT_EQ(s.top(), 499);
}

TEST(TestStack, Push1000Pop500GivesCorrectString)
{
    Stack<string> s;
    for(int i = 0; i < 1000; i++)
    {
        s.push(to_string(i));
    }
    for(int i = 0; i < 500; i++)
    {
        s.pop();
    }
    ASSERT_EQ(s.top(), "499");
}

int main()
{
    ::testing::InitGoogleTest();
    int res = RUN_ALL_TESTS();;

    return res;
}
