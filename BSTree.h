#pragma once
#include "Account.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class BSTree
{
public:

	BSTree();
	BSTree(BSTree &other);
	~BSTree();

	bool Insert(Account *source);

	// retrieve object, first parameter is the ID of the account 
	// second parameter holds pointer to found object, NULL if not found 
	bool Retrieve(const int &ID, Account * &source) const; 

	// displays the contents of a tree to cout 
	void Display() const; 
	void Empty(); 
	bool isEmpty() const; 
	BSTree& operator=(const BSTree &other);

private: 
	struct Node 
	{ 
		Account *pAcct = NULL; 
		Node *right = NULL; 
		Node *left = NULL; 
	}; 
	Node *root; 
	bool insert(Node * &subTree, Account *source);
	bool retrieveHelper(Node *subTree, const int &ID, Account *&name) const;
	void displayPreOrder(Node *pNode) const;
	void clear(Node * &subTree);
	void copy(Node * sourceSubTree);

};

