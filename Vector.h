#pragma once
/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Dimitar Dimitrov
* @idnumber 61970
* @task 3
* @compiler VC
*
*/

template<class T>
class Vector {
public:
	Vector();
	Vector(const Vector&);
	Vector& operator =(const Vector&);
	~Vector();

	void push_back(const T&);
	void pop_back();
	void pop_front();
	void resize(int newSize);
	T& back();
	T& front();
	void insert(int, T);
	void erase(int);
	T& operator[](int);
	int size();
	int capacity();
	bool empty();
	void clear();
	void sort();
private:
	T* elements;
	int m_size;
	int m_capacity;
	void copy(const Vector&);

};

template<class T>
Vector<T>::Vector() {
	elements = new T[0];
	m_size = 0;
	m_capacity = 0;
}

template<class T>
Vector<T>::Vector(const Vector& v) {
	copy(v);
}

template<class T>
Vector<T>& Vector<T>::operator =(const Vector& v) {
	if (this != &v) copy(v);
	return *this;
}

template<class T>
Vector<T>::~Vector() {
	delete[] elements;
}

template<class T>
void Vector<T>::push_back(const T& value) {
	if (m_capacity <= m_size) {
		resize(m_size * 2 + 1);
	}
	elements[m_size] = value;
	m_size++;
}

template<class T>
void Vector<T>::pop_back() {
	m_size = m_size--;
}

template<class T>
void Vector<T>::pop_front() {
	T* arr = new T[size() - 1];
	for (int i = 0; i < m_size - 1; i++)
	{
		arr[i] = elements[i + 1];
	}
	delete[] elements;
	elements = arr;
	m_size = m_size--;
}

template<class T>
void Vector<T>::resize(int newSize) {
	m_capacity = newSize;
	T* new_elements = new T[newSize];
	for (int i = 0; i < m_size; i++)
	{
		new_elements[i] = elements[i];
	}
	delete[] elements;
	elements = new_elements;
}

template<class T>
T& Vector<T>::back() {
	return elements[m_size - 1];
}

template<class T>
T& Vector<T>::front() {
	return elements[0];
}

template<class T>
void Vector<T>::insert(int index, T value) {
	if (m_capacity <= m_size) resize(2 * m_size + 1);
	m_size++;
	for (int i = m_size; i > index; i--)
	{
		elements[i] = elements[i - 1];
	}
	elements[index] = value;
}

template<class T>
void Vector<T>::erase(int index) {
	for (int i = index; i < m_size; i++)
	{
		elements[i] = elements[i + 1];
	}
	m_size--;
}

template<class T>
T& Vector<T>::operator[](int index) {
	return elements[index];
}

template<class T>
int Vector<T>::size() {
	return m_size;
}

template<class T>
int Vector<T>::capacity() {
	return m_capacity;
}

template<class T>
bool Vector<T>::empty() {
	return (m_size == 0);
}

template<class T>
void Vector<T>::clear() {
	delete[] elements;
	m_size = 0;
	m_capacity = 0;
}
template<class T>
void Vector<T>::copy(const Vector& v) {
	m_size = v.m_size;
	m_capacity = v.m_capacity;
	elements = new T[m_size];
	for (int i = 0; i < m_size; i++)
	{
		elements[i] = v.elements[i];
	}
}

template<class T>
void Vector<T>::sort() {
	T	min = elements[0];
	for (int i = 0; i < m_size; i++) {
		for (int j = i; j < m_size; j++) {
			if (elements[i] < min) min = elements[i];
			T temp = min;
			min = elements[j];
			elements[j] = temp;
		}
	}
}

