// BankingApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <vector>
#include "Account.h"
#include "BSTree.h"
#include "Bank.h"
using namespace std;

int main()
{
	/*
	string test = "34";//to see how to use stoi()
	int testin = stoi(test);
	cout << testin << endl;
	vector<int> vtest;//to see what would be the size if we do not initialize it
	cout << vtest.size() << endl;
	Account *acct1 = new Account("Sura", "Alani", 1111);
	acct1->PrintHistory();
	Account *acct2 = new Account("Sura", "Alani", 2222);
	Account *acct3 = new Account("Sura", "Alani", 1001);
	Account *acct4 = new Account("Sura", "Alani", 1201);
	BSTree tree;
	tree.Insert(acct1);
	tree.Insert(acct2);
	tree.Insert(acct3);
	tree.Insert(acct4);
	tree.Display();

	string trans = "O sura alani 1234";
	string first = "";
	int from = 2;
	int to = from;
	while (trans[to] != ' ')
	{
		to++;
	}
	to -= from;
	first = trans.substr(from, to);
	cout << first << endl;
	cout << trans << endl;
	string last = "";
	from += to + 1;
	to = from;
	while (trans[to] != ' ')
	{
		to++;
	}
	to -= from;
	last = trans.substr(from, to);
	cout << last << "" << endl;
	string ID = "";
	from += to + 1;
	ID = trans.substr(from, 4);
	cout << ID << endl;
	cerr << "ERROR: " << ID << " is not a valid ID." << endl;
	*/

	Bank("BankTransIn.txt");
	//cout << "hi";
	//cin.get();
	//cout << "why is it not showing me the results????????";
	//system("pause");
    return 0;
}

