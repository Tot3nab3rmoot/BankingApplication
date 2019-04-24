#pragma once
#include <string>
#include <queue>
#include <fstream>
#include <iostream>
#include "Transactions.h"
#include "BSTree.h"
using namespace std;

class Bank
{
public:
	Bank();
	Bank(string fileName);
	~Bank();
	
	bool BuildQueue(string fileName);
	bool ExecuteQueue();

private:
	BSTree *tree;
	queue<Transactions> qList;
};

