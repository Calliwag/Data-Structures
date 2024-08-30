#include "mssm.h"
#include "gtest/gtest.h"

template <typename T>
class Stack
{
private:

public:
    Stack();
    ~Stack();
    void push(T val);
    T pop();
    T top();
    int size();
    bool isEmpty();
};

template <typename T>
Stack<T>::Stack()
{
    println("Constructor called");
}

template <typename T>
Stack<T>::~Stack()
{
    println("Destructor called");
}

template <typename T>
void Stack<T>::push(T val)
{

}

template <typename T>
T Stack<T>::pop()
{
    return T{};
}

template <typename T>
T Stack<T>::top()
{
    return T{};
}

template <typename T>
int Stack<T>::size()
{
    return -1;
}

template <typename T>
bool Stack<T>::isEmpty()
{
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
    ASSERT_EQ(s.size(), 0);
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
    ASSERT_EQ(s.size(),1);
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
    ASSERT_EQ(s.size(), 1);
}

TEST(TestStack, PushAndPopGivesCorrectValue)
{
    Stack<int> s;
    s.push(1);
    s.push(2);
    s.pop();
    ASSERT_EQ(s.top(), 1);
}

TEST(TestStack, Push1000)
{
    Stack<int> s;
    for(int i = 0; i < 1000; i++)
    {
        s.push(i);
    }
    ASSERT_EQ(s.size(), 1000);
}

int main()
{
    ::testing::InitGoogleTest();
    int res = RUN_ALL_TESTS();;

    return res;
}
