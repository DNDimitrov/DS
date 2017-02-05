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

template <class T>
class List {

private:
	struct Node {
		T m_data;
		Node* m_prev;
		Node* m_next;

		Node(T data, Node* prev = nullptr, Node* next = nullptr) {
			m_data = data;
			m_prev = prev;
			m_next = next;
		}

		bool operator==(Node* other) const {
			return (this->m_data == other->m_data &&
				this->m_prev == other->m_prev &&
				this->m_next == other->m_next);
		}

		bool operator!=(Node* other) const {
			return !(this == other);
		}
	};

private:
	Node* m_first;
	Node* m_last;
	int m_size;

public:
	class Iterator {
	private:
		Node* m_node;

	public:
		Iterator(Node* node) {
			m_node = node;
		}

		T& operator*() const {
			return m_node->m_data;
		}

		Node* get_node() const {
			return m_node;
		}

		Iterator& operator++() {
			m_node = m_node->m_next;
			return *this;
		}

		Iterator operator++(int) {
			Iterator temporary = *this;
			++*this;
			return temporary;
		}

		bool operator==(Iterator other) const {
			return (this->m_node == other.m_node);
		}

		bool operator!=(Iterator other) const {
			return (this->m_node != other.m_node);
		}
	};

public:
	List();
	~List();
	void push_front(const T&);
	void pop_front();
	void push_back(const T&);
	void pop_back();
	T& front();
	T& back();
	void insert_before(Iterator, const T&);
	void insert_after(Iterator, const T&);
	void erase(Iterator);

	Iterator begin();
	Iterator last(); // returns iterator to the last element
	Iterator end(); // returns iterator to one after the last element
	int size();
	void clear();
	void print();
	bool empty();

private:
	void destroy_chain();
	void init();
};


template <class T>
List<T>::List() {
	init();
}

template <class T>
List<T>::~List() {
	destroy_chain();
	init();
}

template <class T>
void List<T>::push_front(const T& value) {
	insert_before(begin(), value);
}

template <class T>
void List<T>::pop_front() {
	erase(begin());
}

template <class T>
void List<T>::push_back(const T& value) {
	insert_after(last(), value);
}

template <class T>
void List<T>::pop_back() {
	erase(last());
}

template <class T>
T& List<T>::front() {
	return m_first->m_data;
}

template <class T>
T& List<T>::back() {
	return m_last->m_data;
}

template <class T>
void List<T>::insert_before(Iterator it, const T& value) {
	Node* node = it.get_node();
	Node* new_node = new Node(value);

	if (empty()) {
		m_first = new_node;
		m_last = new_node;
		m_size += 1;
		return;
	}

	new_node->m_next = node;
	node->m_prev = new_node;

	if (it == begin()) {
		m_first = new_node;
	}
	else {
		new_node->m_prev = node->m_prev;
		node->m_prev->m_next = new_node;
	}

	m_size += 1;
}

template <class T>
void List<T>::insert_after(Iterator it, const T& value) {
	Node* node = it.get_node();
	Node* new_node = new Node(value);

	if (empty()) {
		m_first = new_node;
		m_last = new_node;
		m_size += 1;

		return;
	}

	if (it == last()) {
		new_node->m_prev = node;
		node->m_next = new_node;
		m_last = new_node;

		m_size += 1;
	}
	else {
		insert_before(Iterator(node->m_next), value);
	}
}

template <class T>
void List<T>::erase(Iterator it) {
	if (m_size == 1) {
		init();
	}
	else if (empty() == false) {

		m_size -= 1;
		Node* to_erase;

		if (it == begin()) {
			to_erase = m_first;
			m_first = m_first->m_next;

			delete to_erase;
		}
		else if (it == last()) {
			to_erase = m_last;
			m_last = m_last->m_prev;

			delete to_erase;
		}
		else {
			to_erase = it.get_node();
			to_erase->m_prev->m_next = to_erase->m_next;
			to_erase->m_next->m_prev = to_erase->m_prev;

			delete to_erase;
		}
	}
}

template <class T>
typename List<T>::Iterator List<T>::begin() {
	return Iterator(m_first);
}

template <class T>
typename List<T>::Iterator List<T>::last() {
	return Iterator(m_last);
}

template <class T>
typename List<T>::Iterator List<T>::end() {
	return ++last();
}

template <class T>
int List<T>::size() {
	return m_size;
}

template <class T>
void List<T>::clear() {
	destroy_chain();
	init();
}


template <class T>
void List<T>::print() {
	if (empty() == false) {
		for (Iterator it = begin(); it != end(); it++) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
}

template <class T>
bool List<T>::empty() {
	return (m_size == 0);
}

template <class T>
void List<T>::destroy_chain() {
	Node* temporary = m_first;
	while (temporary != nullptr) {
		m_first = m_first->m_next;
		delete temporary;
		temporary = m_first;
	}
}

template <class T>
void List<T>::init() {
	m_size = 0;
	m_first = nullptr;
	m_last = nullptr;
}