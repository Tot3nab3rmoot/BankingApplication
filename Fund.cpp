#include "stdafx.h"
#include "Fund.h"
#include <fstream>


Fund::Fund()
{
	name = "";
	balance = 0;
	//history.push_back("");
}


Fund::~Fund()
{
}

int Fund::getBalance() const
{
	return balance;
}

string Fund::getName() const
{
	return name;
}

bool Fund::setBalance(int bal)
{
	balance = bal;
	//cout << "setBalance is called Balance is: $" << balance << endl;
	return true;
}

bool Fund::setName(string nam)
{
	name = nam;
	return true;
}

void Fund::LogToHistory(string log)
{
	history.push_back(log);
}

void Fund::Print() const
{
	//ofstream myfile;
	//myfile.open("BankTransOut.txt");
	//myfile << name << ": $" << balance << endl;
	//myfile.close();
	cout << name << ": $" << balance << endl;
}

void Fund::PrintHistory() const
{
	if (history.size() <= 0) 
	{
		return;
	}
	cout << "   " << name << ": $" << balance << endl;
	for (int i = 0; i < history.size(); i++)
	{
		cout << "     " << history[i] << endl;
	}
}
