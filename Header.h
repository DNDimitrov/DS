template<class T>
class Vector {
private:
	T* elements;
	int m_size;
	int m_capacity;
	void copy(const Vector&);
public:
	Vector();
	Vector(const Vector&);
	~Vector();
	Vector& operator=(const Vector&);
	void push_back(const T&);
	void pop_back();
	void pop_front();
	void resize(int newSize);
	void clear();
	T& operator[](int);
	int size();
	int capacity();
	bool empty();
	T& back();
	T& front();
	void sort();

};

template<class T>
Vector<T>::Vector() {
	elements = new T[0];
	m_capacity = 0;
	m_size = 0;
}

template<class T>
Vector<T>::Vector(const Vector& v) {
	copy(v);
}

template<class T>
Vector<T>::~Vector() {
	delete[] elements;
}
template<class T>
Vector<T>& Vector<T>::operator=(const Vector& v) {
	if (this != v) copy(v);
	return *this;
}
template<class T>
void Vector<T>::resize(int newSize) {
	m_capacity = newSize;
	T* new_element = new T[newSize];
	for (int i = 0; i < m_size; i++) {
		new_element[i] = elements[i];
	}
	delete[] elements;
	elements = new_element;
}
template<class T>
void Vector<T>::push_back(const T& other) {
	if (m_capacity <= m_size)
		resize(2 * m_size + 1);
	elements[m_size] = other;
	m_size++;
}

template<class T>
void Vector<T>::pop_back() {
	m_size = m_size--;
}

template<class T>
void Vector<T>::pop_front() {
	T* arr = new T[m_size - 1];
	for (int i = 0; i < m_size - 1; i++) {
		arr[i] = elements[i + 1];
	}
	delete[] elements;
	elements = arr;
	m_size--;
}

template<class T>
T& Vector<T>::front() {
	return elements[0];
}

template<class T> 
T& Vector<T>::back() {
	return elements[m_size - 1];

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
	return (m_size==0);
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
	for (int i = 0; i < m_size; i++) {
		elements[i] = v.elements[i];
	}
}

template<class T>
void Vector<T>::sort() {
	int i, j;
	for (i = 0; i < m_size; i++) {
		T temp = elements[i];
		for (j = i; j > 0 && elements[j] > temp; j--) {
			elements[j] = elements[j - 1];
		}
		elements[j] = temp;
	}
}