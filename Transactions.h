#pragma once
#include "Account.h"
#include "BSTree.h"

class Transactions
{
	friend istream& operator>>(istream &in, Transactions &transac);
public:
	Transactions();
	Transactions(string trans);
	/*Transactions(string type, string idAndFund, int money);
	Transactions(string type, string first, string last, string ID);
	Transactions(string type, string acctAndFund1, int money, string acctAndFund2);
	Transactions(string type, string idAndFund)*/
	~Transactions();
	void ExecuteTrans(BSTree *tree);

	bool SliceO(BSTree *&tree);//should be done :)
	bool O(string first, string last, string id, BSTree *&tree);//should be done :)

	bool SliceH(BSTree *tree);//should be done :)
	bool HAcct(BSTree *tree, string id);//should be done :)
	bool HFund(BSTree *tree, string id, string fundNum);//should be done :)

	bool SliceD(BSTree *tree);//should be done :)
	bool D(BSTree *tree, string id, string fundNum, string money);//should be done :)

	bool SliceW(BSTree *tree);
	bool W(BSTree *tree, string id, string fundNum, string money);

	bool SliceT(BSTree *tree);
	bool T(BSTree *tree, string idFrom, string fundNumFrom, string money, string idTo, string fundNumTo);

	void Print();

private:
	string trans;
	/*string type;
	string idAndFund;
	int money;*/
};

