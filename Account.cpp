#include "stdafx.h"
#include "Account.h"
#include <fstream>
using namespace std;

Account::Account()
{
	first = "";
	last = "";
	int ID = -1;
	//history.push_back("");
	//make funds
	for (int i = 0; i < 10; i++)
	{
		Fund temp;
		temp.setName(FUND_NAME[i]);
		funds.push_back(temp);
	}
}

Account::Account(string theFirst, string theLast, int theID)
{
	first = theFirst;
	last = theLast;
	ID = theID;
	//history.push_back("");
	//make funds
	for (int i = 0; i < 10; i++)
	{
		Fund temp;
		temp.setName(FUND_NAME[i]);
		funds.push_back(temp);
	}
}


Account::~Account()
{
}

int Account::getID() const
{
	return ID;
}

string Account::getName() const
{
	return first + " " + last;
}

vector<Fund> Account::getFunds() const
{
	return funds;
}

bool Account::ChangeFundBalance(int balance, int fundNum)
{
	funds[fundNum].setBalance(balance);
	return true;
}

bool Account::LogToFundHistory(string trans, int fundNum)
{
	funds[fundNum].LogToHistory(trans);
	return true;
}

void Account::Print() const
{
	/*cout << first << " " << last << " Account ID: " << ID << endl;
	ofstream myfile;
	myfile.open("BankTransOut.txt");
	/*myfile << first << " " << last << " Account ID: " << ID << endl;
	for (int i = 0; i < funds.size(); i++)
	{
		myfile << "   ";
		funds[i].Print();
	}
	myfile.close();//
	if (myfile.is_open())
	{
		myfile << first << " " << last << " Account ID: " << ID << endl;
		//myfile << "This is a line.\n";
		for (int i = 0; i < funds.size(); i++)
		{
			myfile << "   ";
			funds[i].Print(myfile);
		}
		myfile.close();
	}*/

	cout << first << " " << last << " Account ID: " << ID << endl;
	for (int i = 0; i < funds.size(); i++)
	{
		cout << "   ";
		funds[i].Print();
	}
}

void Account::PrintHistory() const
{
	cout << "Transaction History for " << first << " " << last << " by fund." << endl;
	for (int i = 0; i < funds.size(); i++)
	{
		//cout << "   ";
		//FUND_NAME[i];
		funds[i].PrintHistory();
	}
}

bool Account::operator==(const Account & other)
{
	return (ID == other.ID);
}

bool Account::operator>(const Account & other)
{
	return (ID > other.ID);
}

bool Account::operator<(const Account & other)
{
	return (ID < other.ID);
}


/*
ostream & operator<<(ostream & outStream, const Account & acct)
{
	outStream << "Transaction History for " << acct.first << acct.last << " by fund." << endl << acct.funds[0];
	//outStream << acct.funds[0] <<
}
*/