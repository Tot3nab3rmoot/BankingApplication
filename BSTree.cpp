#include "stdafx.h"
#include "BSTree.h"


BSTree::BSTree()
{
	root = NULL;
}

BSTree::BSTree(BSTree & other)
{
	*this = other;
}


BSTree::~BSTree()
{
	clear(root);
}

bool BSTree::Insert(Account *source)
{
	if (root == NULL)
	{
		root = new Node;
		root->pAcct = new Account;
		*(root->pAcct) = *source;
		return true;
	}
	else
	{
		return insert(root, source);
	}
}

bool BSTree::insert(Node * &subTree, Account *source)
{
	if (subTree == NULL)
	{
		subTree = new Node;
		subTree->pAcct = new Account;
		*(subTree->pAcct) = *source;
		return true;
	}
	if (*(subTree->pAcct) == *source)
	{
		return false;
	}
	if (*(subTree->pAcct) > *source)
	{
		return insert(subTree->left, source);
	}
	else
	{
		return insert(subTree->right, source);
	}
}

bool BSTree::Retrieve(const int &ID, Account *&source) const
{
	if (root == NULL)
	{
		source = NULL;
		return false;
	}
	else
	{
		return retrieveHelper(root, ID, source);
	}
}

bool BSTree::retrieveHelper(Node *subTree, const int &ID, Account *&source) const
{
	if (subTree == NULL)
	{
		source = NULL;
		return false;
	}
	else if (subTree->pAcct->getID() == ID)
	{
		source = subTree->pAcct;
		return true;
	}
	if (subTree->pAcct->getID() > ID)
	{
		return retrieveHelper(subTree->left, ID, source);
	}
	else
	{
		return retrieveHelper(subTree->right, ID, source);
	}
}

void BSTree::Display() const
{
	cout << "Processing Done. Final Balances" << endl;
	displayPreOrder(root);
}

void BSTree::displayPreOrder(Node * pNode) const
{
	if (pNode != NULL)
	{
		pNode->pAcct->Print();
		displayPreOrder(pNode->left);
		displayPreOrder(pNode->right);
	}
}

void BSTree::Empty()
{
	clear(root);
}

void BSTree::clear(Node *& subTree)
{
	if (subTree == NULL)
	{
		return;
	}
	if (subTree->left != NULL)
	{
		clear(subTree->left);
	}
	if (subTree->right != NULL)
	{
		clear(subTree->right);
	}
	delete subTree->pAcct;
	subTree->pAcct = NULL;
	delete subTree;
	subTree = NULL;
}

bool BSTree::isEmpty() const
{
	return (root == NULL);
}

BSTree & BSTree::operator=(const BSTree &other)
{
	if (this == &other)
	{
		return *this;
	}
	clear(this->root);
	this->copy(other.root);
	return *this;
}

void BSTree::copy(Node * sourceSubTree)
{
	if (sourceSubTree == NULL)
	{
		return;
	}
	Insert(sourceSubTree->pAcct);
	copy(sourceSubTree->left);
	copy(sourceSubTree->right);
}