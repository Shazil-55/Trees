#pragma once
#include <iostream>
using namespace std;

template <typename T >
class Queue
{
	int rear;
	int front;
	int noe;
	int capacity;
	T* data;
	void reSize(int newsize)
	{
		T* temp = new T[newsize];
		noe = rear;
		for (int i = 0; i < noe; i++)
			temp[i] = data[i];
		this->~Queue();
		rear = noe;
		data = temp;
		capacity = newsize;
	}
public:
	Queue();
	Queue(const Queue <T>& rhs);
	Queue& operator = (const Queue<T>& rhs);
	~Queue();
	void enQueue(T);
	void change(T);
	T deQueue();
	T getElementsAtFront() const;
	bool isEmpty()const;
	bool isFull()const;
	int getCapacity() const;
	int getNumberOfElements() const;
};

