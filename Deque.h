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
#include<stdexcept>

using namespace std;

template<typename T> class Deque
{
private:
	class Node
	{
		friend class Deque;
	public:
		Node()
		{
			next = nullptr;
			previous = nullptr;
		}
		Node(Node* Next, Node* Previous, T Data)
		{
			next = Next;
			previous = Previous;
			data = Data;
		}
	private:
		Node* previous;
		Node* next;
		T data;
	};
public:
	Deque()
	{
		head = new Node();
		tail = new Node();
		head->next = tail;
		tail->previous = head;
		size = 0;
	}
	Deque(const Deque& other)
	{
		head = new Node();
		tail = new Node();
		head->next = tail;
		tail->previous = head;
		Node* currentElement = other.head->next;
		for (int i = 0; i<other.size; i++)
		{
			pushBack(currentElement->data);
			currentElement = currentElement->next;
		}
	}

	const Deque& operator= (const Deque& other)
	{
		clear();
		Node* currentElement = other.head->next;
		for (int i = 0; i < other.size(); i++)
		{
			pushBack(currentElement->data);
			currentElement = currentElement->next;
		}
	}

	void clear()
	{
		while (size != 0)
		{
			popBack();
		}
	}

	~Deque()
	{
		clear();
		delete head;
		delete tail;
	}

	T getFirst() const
	{
		if (size == 0)
		{
			throw runtime_error("0 elements");
		}
		return head->next->data;
	}

	T getLast() const
	{
		if (size == 0)
		{
			throw runtime_error("0 elements");
		}
		return tail->previous->data;
	}

	void pushBack(T data)
	{
		Node* newNode = new Node(tail, tail->previous, data);
		tail->previous->next = newNode;
		tail->previous = newNode;
		size++;
	}

	void popBack()
	{
		if (size == 0)
		{
			throw runtime_error("Can't pop from empty dq");
		}
		Node* toDelete = tail->previous;
		tail->previous->previous->next = tail;
		tail->previous = tail->previous->previous;
		delete toDelete;
		size--;

	}

	void pushFront(T data)
	{
		Node* newNode = new Node(head->next, head, data);
		head->next->previous = newNode;
		head->next = newNode;
		size++;
	}

	void popFront()

	{
		if (size == 0)
		{
			throw runtime_error("Can't pop from empty dq");
		}
		Node* toDelete = head->next;
		head->next->next->previous = head;
		head->next = head->next->next;
		delete toDelete;
		size--;

	}
	bool isEmpty() const
	{
		return size == 0;
	}
	int getSize() const
	{
		return size;
	}

private:
	Node* head;
	Node* tail;
	int size;
};
