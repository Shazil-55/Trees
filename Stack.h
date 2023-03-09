#pragma once
#include<iostream>
using namespace std;
template<typename T>
class Stack
{
    T* data;
    int capacity;
    int top;
    void reSize(int c)
    {
        T* temp = new T[c];
        int noe = top;
        for (int i = 0; i < top; i++)
            temp[i] = data[i];
        this->~Stack();
        top = noe;
        data = temp;
        capacity = c;

    }
public:
    Stack();
    Stack(const Stack<T>& rhs);
    Stack& operator = (const Stack<T>& rhs)
    {
        capacity = rhs.capacity;
        top = rhs.top;
        for (int i = 0; i < top; i++)
        {
            data[i] = rhs.data[i];
        }
    }
    ~Stack();
    void push(T);
    T pop();
    T stackTop() const;
    bool isFull() const;
    bool isEmpty() const;
    int getCapacity() const;
    int getNumberOfElements() const;
};
template < typename T>
Stack<T>::Stack()
{
    capacity = 0;
    data = nullptr;
    top = 0;
}

template < typename T>
Stack<T>::Stack(const Stack<T>& rhs)
{
    capacity = rhs.capacity;
    top = rhs.top;
    for (int i = 0; i < top; i++)
    {
        data[i] = rhs.data[i];
    }

}
template < typename T>
Stack<T> ::~Stack()
{
    if (data != nullptr)
    {
        delete[] data;
        data = nullptr;
        capacity = 0;
        top = 0;
    }
}

template < typename T>
void Stack<T> ::push(T a)
{
    if (isFull())
    {
        reSize(capacity == 0 ? 1 : capacity * 2);
    }
    data[top] = a;
    top++;
}

template < typename T>
T Stack<T> ::pop()
{
    if (isEmpty()) exit(0);
    top--;
    T val = data[top];
    if (top > 0 && (capacity / 4) == top) reSize(capacity / 2);
    return val;
}

template < typename T>
T Stack<T> ::stackTop() const
{

    if (isEmpty()) exit(0);
    return data[top - 1];
}

template < typename T>
bool Stack<T> ::isFull() const
{
    if (top == capacity)return true;
    return  false;
}

template < typename T>
bool Stack<T> ::isEmpty() const
{
    if (top == 0)return true;
    return  false;
}

template < typename T>
int Stack<T> ::getCapacity() const
{
    return capacity;
}

template < typename T>
int Stack<T> ::getNumberOfElements() const
{
    return top;
}