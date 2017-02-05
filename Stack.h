/*
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Dimitar Dimitrov
* @idnumber 61970
* @task 2
* @compiler VC
*
*/

#pragma once
#include <stdexcept>

template <typename T> class Stack
{
public:
	Stack()
	{
		data = new T[16];
		capacity = 16;
		size = 0;
	}
	~Stack()
	{
		delete[] data;
	}
	void pop()
	{
		if (size == 0)
		{
			throw std::runtime_error("Can't pop from an empty stack.");
		}
		size--;
	}
	void push(T newElement)
	{
		if (size == capacity)
		{
			resize(size * 2 + 1);
		}
		data[size] = newElement;
		size++;
	}
	T getElement() const
	{
		return data[size - 1];
	}
	bool isEmpty() const
	{
		return size == 0;
	}

private:
	void resize(int newCapacity)
	{
		T* newData = new T[newCapacity];
		for (int i = 0; i < size; i++)
		{
			newData[i] = data[i];
		}
		delete[] data;
		data = newData;
		capacity = newCapacity;
	}

private:
	T* data;
	int capacity;
	int size;
};

