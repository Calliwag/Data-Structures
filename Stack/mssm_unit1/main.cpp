#include "mssm.h"
#include "gtest/gtest.h"

template <typename T>
class Node
{
private:

public:
    T value;
    Node<T>* next;


    Node(T _value, Node<T>* _next);
    Node(T _value);
    ~Node();
};

template <typename T>
Node<T>::Node(T _value, Node<T>* _next)
{
    value = _value;
    next = _next;
}

template <typename T>
Node<T>::Node(T _value)
{
    value = _value;
    next = nullptr;
}

template <typename T>
Node<T>::~Node()
{
    next = nullptr;
}

template <typename T>
class Stack
{
private:
    Node<T>* headPtr;
    int size;

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
    headPtr = nullptr;
    size = 0;
}

template <typename T>
Stack<T>::~Stack()
{
    Node<T>* currentPtr = headPtr;
    while(currentPtr != nullptr)
    {
        Node<T>* newCurrentPtr = currentPtr->next;
        delete currentPtr;
        currentPtr = newCurrentPtr;
    }
}

template <typename T>
void Stack<T>::push(T val)
{
    Node<T>* newNode = new Node<T>(val, headPtr);
    headPtr = newNode;
    size++;
}

template <typename T>
T Stack<T>::pop()
{
    Node<T>* newHeadPtr = headPtr->next;
    T value = headPtr->value;
    delete headPtr;
    headPtr = newHeadPtr;
    size--;
    return value;
}

template <typename T>
T Stack<T>::top()
{
    return headPtr->value;
}

template <typename T>
int Stack<T>::getSize()
{
    return size;
}

template <typename T>
bool Stack<T>::isEmpty()
{
    if(size == 0) return 1;
    else return 0;
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
