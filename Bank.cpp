#include "stdafx.h"
#include "Bank.h"


Bank::Bank()
{
}

Bank::Bank(string fileName)
{
	tree = new BSTree;
	BuildQueue(fileName);
	//cout << "Bank is called" << endl;
}


Bank::~Bank()
{
	delete tree;
	tree = NULL;
}

bool Bank::BuildQueue(string fileName)
{
	//cout << "BuildQueue is called" << endl;
	string line;
	ifstream inFile;
	inFile.open(fileName);
	if (inFile.is_open())
	{
		//cout << "file is opened" << endl;
		while (getline(inFile, line))//to get the line completely
		{
			Transactions trans(line);
			qList.push(trans);
		//	trans.Print();
		}

		inFile.close();
		return ExecuteQueue();
	}
	else
	{
		//cout << "File: " << fName << "not found" << endl;
		return false;
	}
}

bool Bank::ExecuteQueue()
{
	std::ofstream out("BankTransOut.txt");
	std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
	std::cout.rdbuf(out.rdbuf());
	std::streambuf *cerrbuf = std::cerr.rdbuf(); //save old buf
	std::cerr.rdbuf(out.rdbuf());

	while (!qList.empty())
	{
		Transactions temp = qList.front();
		temp.ExecuteTrans(tree);
		qList.pop();
	}
	//cout << "reached ExecuteQueue" << endl;
	tree->Display();
	return true;
}
