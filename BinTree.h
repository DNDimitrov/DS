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
* @task 4
* @compiler VC
*
*/
#include"Vector.h"
#include<string>

using namespace std;

template<typename T> class readNode
{
public:
	readNode(T newKey, string newData)
	{
		key = newKey;
		data.push_back(newData);
	}
	readNode()
	{

	}

	bool operator<(readNode<T> other)
	{
		if (key < other.key)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool operator>(readNode<T> other)
	{
		if (key > other.key)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	T getKey() { return key; }
	Vector<string>& getData() { return data; }
	void addData(string newString)
	{
		data.push_back(newString);
	}
private:
	T key;
	Vector<string> data;
};

template<typename T> class Node
{
public:
	T key;
	Node* left;
	Node* right;
	Vector<string> data;
};

template<typename T> class BiTree
{
public:
	BiTree()
	{
		root = nullptr;
		size = 0;
	}

	~BiTree() { clear(root); }

	Node<T>* buildFromArr(Vector<readNode<T>> arr, int start, int end)
	{
		if (start > end)
		{
			return nullptr;
		}
		int middle = (start + end) / 2;
		size++;
		Node<T>* node = new Node<T>();
		node->left = nullptr;
		node->right = nullptr;
		node->key = arr[middle].getKey();
		node->data = arr[middle].getData();

		node->left = buildFromArr(arr, start, middle - 1);

		node->right = buildFromArr(arr, middle + 1, end);

		return node;
	}


	void build(Vector <readNode<T>> arr)
	{
		root = buildFromArr(arr, 0, arr.size() - 1);
	}

	//if exists
	bool search(int keyToFind, string dataToFind)
	{
		return searchNode(keyToFind, dataToFind, root);
	}
	//which node is
	Node<T>* searchNode(int keyToFind, string dataToFind, Node<T>* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		if (node->key == keyToFind)
		{
			for (int i = 0; i < node->data.size(); i++)
			{
				if (node->data[i] == dataToFind)
				{
					return node;
				}
			}
			return nullptr;
		}
		else
		{
			if (keyToFind < node->key)
			{
				return searchNode(keyToFind, dataToFind, node->left);
			}
			else
			{
				return searchNode(keyToFind, dataToFind, node->right);
			}
		}
	}

	//search only if key exists
	Node<T>* searchKeyNode(int keyToFind, Node<T>* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}

		if (node->key == keyToFind)
		{
			return node;
		}
		else
		{
			if (keyToFind < node->key)
			{
				return searchKeyNode(keyToFind, node->left);
			}
			else
			{
				return searchKeyNode(keyToFind, node->right);
			}
		}
	}

	void insert(int newKey, string newData)
	{
		insertPr(newKey, newData, root);
		size++;
	}


	void insertPr(int keyToInsert, string dataToInsert, Node<T>*& node)
	{
		if (node == nullptr)
		{
			node = new Node<T>();
			node->key = keyToInsert;
			node->data.push_back(dataToInsert);
			node->left = nullptr;
			node->right = nullptr;
			return;
		}

		if (node->key == keyToInsert)
		{
			node->data.push_back(dataToInsert);
			return;
		}
		else
		{
			if (keyToInsert < node->key)
			{
				if (node->left != nullptr)
				{
					insertPr(keyToInsert, dataToInsert, node->left);
				}
				else
				{
					node->left = new Node<T>();
					node->left->key = keyToInsert;
					node->left->data.push_back(dataToInsert);
					node->left->left = nullptr;
					node->left->right = nullptr;
				}
			}
			else
			{
				if (node->right != nullptr)
				{
					insertPr(keyToInsert, dataToInsert, node->right);
				}
				else
				{
					node->right = new Node<T>();
					node->right->key = keyToInsert;
					node->right->data.push_back(dataToInsert);
					node->right->left = nullptr;
					node->right->right = nullptr;
				}
			}
		}
	}
	bool remove(int keyToRemove, string dataToRemove)
	{
		Node<T>* nodeToRemove = searchNode(keyToRemove, dataToRemove, root);
		if (nodeToRemove == nullptr)
		{
			return 0;
		}

		if (nodeToRemove->data.size() > 1)
		{
			for (int i = 0; i < nodeToRemove->data.size(); i++)
			{
				if (dataToRemove == nodeToRemove->data[i])
				{
					nodeToRemove->data.erase(i);
					size--;
					return true;
				}
			}
			return false;
		}

		if (nodeToRemove->data[0] != dataToRemove)
		{
			return false;
		}

		if (nodeToRemove->left == nullptr && nodeToRemove->right == nullptr)
		{
			delete nodeToRemove;
			nodeToRemove = nullptr;
		}
		else if (nodeToRemove->left != nullptr && nodeToRemove->right == nullptr)
		{
			Node<T>* tmp = nodeToRemove;
			nodeToRemove = nodeToRemove->left;
			delete tmp;
		}
		else
		{
			Node<T>* maxOnLeft = findMax(nodeToRemove->left);
			nodeToRemove->key = maxOnLeft->key;
			nodeToRemove->data = maxOnLeft->data;
			delete maxOnLeft;
			maxOnLeft = nullptr;
		}
		size--;
		return true;
	}

	int removeAll(int keyToRemove)
	{
		Node<T>* nodeToRemove = searchKeyNode(keyToRemove, root);
		if (nodeToRemove == nullptr)
		{
			return 0;
		}
		int sizeOf = nodeToRemove->data.size();
		if (nodeToRemove->left == nullptr && nodeToRemove->right == nullptr)
		{
			nodeToRemove = nullptr;
			delete nodeToRemove;
			return sizeOf;
		}
		else if (nodeToRemove->left != nullptr && nodeToRemove->right == nullptr)
		{
			Node<T>* tmp = nodeToRemove;
			nodeToRemove = nodeToRemove->left;
			delete tmp;
			return sizeOf;
		}
		else if (nodeToRemove->left == nullptr && nodeToRemove->right != nullptr)
		{
			Node<T>* tmp = nodeToRemove;
			nodeToRemove = nodeToRemove->right;
			delete tmp;
			return sizeOf;
		}
		else
		{
			Node<T>* maxOnLeft = findMax(nodeToRemove->left);
			nodeToRemove->key = maxOnLeft->key;
			nodeToRemove->data = maxOnLeft->data;
			delete maxOnLeft;
			maxOnLeft = nullptr;
			return sizeOf;

		}
		size--;
	}

	Node<T>* findMax(Node<T>* node)
	{
		if (node == nullptr)
		{
			return nullptr;
		}
		if (node->right == nullptr)
		{
			return node;
		}
		else
		{
			return findMax(node->right);
		}
	}

	void clear(Node<T>* Nodes)
	{
		if (Nodes)
		{
			clear(Nodes->left);
			clear(Nodes->right);
			delete Nodes;
		}
	}
private:
	Node<T>* root;
	int size;
};