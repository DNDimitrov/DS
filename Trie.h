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

#include <iostream>
#include "Vector.h"
using namespace std;

class Node {
public:
	Node() { mContent = ' '; mMarker = false; }
	~Node() {}
	char content() { return mContent; }
	void setContent(char c) { mContent = c; }
	bool wordMarker() { return mMarker; }
	void setWordMarker() { mMarker = true; }
	void setValue(int value) { mValue = value; }
	Node* findChild(char c);
	void appendChild(Node* child) { mChildren.push_back(child); }
	Vector<Node*> children() { return mChildren; }
	int getValue() const { return mValue; }

private:
	int mValue;
	char mContent;
	bool mMarker;
	Vector<Node*> mChildren;
};

class Trie {
public:
	Trie();
	~Trie();
	void addWord(string s, int value);
	std::pair<bool, int> searchWord(string s);
private:
	void deleteTrie(Node* nextNode);
	Node* root;
};

Node* Node::findChild(char c)
{
	for (int i = 0; i < mChildren.size(); i++)
	{
		Node* tmp = mChildren[i];
		if (tmp->content() == c)
		{
			return tmp;
		}
	}

	return NULL;
}

Trie::Trie()
{
	root = new Node();
}

void Trie::deleteTrie(Node* nextNode)
{
	for (int i = 0; i < nextNode->children().size(); i++)
	{
		if (nextNode->children()[i] != nullptr)
		{
			deleteTrie(nextNode->children()[i]);
			delete nextNode->children()[i];
		}
	}
}

Trie::~Trie()
{
	deleteTrie(root);
}

void Trie::addWord(string s, int value)
{
	Node* current = root;

	if (s.length() == 0)
	{
		current->setWordMarker(); // an empty word
		return;
	}

	for (int i = 0; i < s.length(); i++)
	{
		Node* child = current->findChild(s[i]);
		if (child != NULL)
		{
			current = child;
		}
		else
		{
			Node* tmp = new Node();
			tmp->setContent(s[i]);
			current->appendChild(tmp);
			current = tmp;
		}
		if (i == s.length() - 1)
		{
			current->setWordMarker();
			current->setValue(value);

		}
	}
}


std::pair<bool, int> Trie::searchWord(string s)
{
	Node* current = root;

	while (current != NULL)
	{
		for (int i = 0; i < s.length(); i++)
		{
			Node* tmp = current->findChild(s[i]);
			if (tmp == NULL)
				return std::pair<bool, int>(false, 0);
			current = tmp;
		}

		if (current->wordMarker())
		{
			return std::pair<bool, int>(true, current->getValue());
		}
		else
		{
			return std::pair<bool, int>(false, 0);
		}
	}

	return std::pair<bool, int>(false, 0);
}

