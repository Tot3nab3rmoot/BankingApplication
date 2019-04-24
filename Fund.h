#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Fund
{
public:
	Fund();
	~Fund();
	//setMoney and getMoney
	int getBalance() const;
	string getName() const;
	bool setBalance(int bal);
	bool setName(string nam);

	void LogToHistory(string log);
	//print to print history
	void Print()const;
	void PrintHistory() const;
private:
	string name;
	int balance;
	vector<string> history;
};

