#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Fund.h"
using namespace std;

//To use when printing out the funds
const vector<string> FUND_NAME {"Money Market", "Prime Money Market", "Long-Term Bond", "Short-Term Bond", "500 Index Fund", "Capital Value Fund", "Growth Equity Fund", "Growth Index Fund", "Value Fund", "Value Stock Index"};

class Account
{
	//friend ostream& operator<<(ostream &outStream, const Account &acct);

public:
	Account();
	Account(string first, string last, int ID);//Or I could take ID as a strin and change it to int in here
	~Account();

	int getID() const;//or I could make it change ID to string and retrun it as a string
	string getName() const;
	vector<Fund> getFunds() const;
	
	bool ChangeFundBalance(int balance, int fundNum);//because funds is a private data
	bool LogToFundHistory(string trans, int fundNum);//because funds is a private data
	void Print() const;
	void PrintHistory() const;
	bool operator==(const Account &other);
	bool operator>(const Account &other);
	bool operator<(const Account &other);

private:
	string first;
	string last;
	int ID;
	vector<string> history;
	//or a vector for funds
	vector<Fund> funds;
//	Fund moneyMarket;
//	Fund one;
	//int balance; 
};

