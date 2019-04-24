#include "stdafx.h"
#include "Transactions.h"


Transactions::Transactions()
{
}

Transactions::Transactions(string theTrans)
{
	trans = theTrans;
	Fund fund;
}


Transactions::~Transactions()
{
}

void Transactions::ExecuteTrans(BSTree *tree)
{
	if (trans[0] == 'O')
	{
		SliceO(tree);
		return;
	}
	else if (trans[0] == 'H')
	{
		SliceH(tree);
		return;
	}
	else if (trans[0] == 'D')
	{
		SliceD(tree);
		return;
	}
	else if (trans[0] == 'W')
	{
		SliceW(tree);
		return;
	}
	else if (trans[0] == 'T')
	{
		SliceT(tree);
		return;
	}
}

bool Transactions::SliceO(BSTree *&tree)
{
	string first = "";
	int from = 2;
	int to = from;
	while (trans[to] != ' ')
	{
		to++;
	}
	to -= from;
	first = trans.substr(from, to);

	string last = "";
	from += to + 1;
	to = from;
	while (trans[to] != ' ')
	{
		to++;
	}
	to -= from;
	last = trans.substr(from, to);

	string ID = "";
	from += to + 1;
	ID = trans.substr(from, 4);
	to = trans.length() - from;
	if (to != 4) 
	{
		cerr << "ERROR: " << trans.substr(from, to) << " is not a valid ID. Transaction refused." << endl;
		return false;
	}
	return O(last, first, ID, tree);
}

bool Transactions::O(string first, string last, string id, BSTree *&tree)
{
	int ID = stoi(id);
	Account *pTemp = new Account(first, last, ID);
	bool successful;
	successful = tree->Insert(pTemp);
	if (!successful)
	{
		cerr << "ERROR: Account " << ID << " is already open. Transaction refused." << endl;
		return false;
	}
	return true;
}

bool Transactions::SliceH(BSTree * tree)
{
	if (trans.length() == 6)//history of the account
	{
		string ID = trans.substr(2, 4);
		return HAcct(tree, ID);
	}
	else if (trans.length() == 7)
	{
		string ID = trans.substr(2, 4);
		string fundNum = trans.substr(6, 1);
		return HFund(tree, ID, fundNum);
	}
	else
	{
		cerr << "ERROR: Transaction (" << trans << ") is invalid.Transaction refused." << endl;
		return false;
	}
}

//Display the history of all transactions of all accounts for a client 
bool Transactions::HAcct(BSTree * tree, string id)
{
	Account *acct = NULL;
	int ID = stoi(id);//change to int
	bool found;
	found = tree->Retrieve(ID, acct);
	if (!found)
	{
		cerr << "ERROR: Account " << ID << " not found to print the history. Transaction refused." << endl;
		return false;
	}
	acct->PrintHistory();
	return true;
}

// Display the history of all transactions of a fund for a client
bool Transactions::HFund(BSTree * tree, string id, string fundNum)
{
	Account *acct = NULL;
	int ID = stoi(id);//change to int
	bool found;
	found = tree->Retrieve(ID, acct);
	if (!found)
	{
		cerr << "ERROR: Account " << ID << " not found. Tranaction refused." << endl;
		return false;
	}
	int fNum = stoi(fundNum);
	/*if (fNum > 9)
	{
		cerr << "ERROR: Fund " << fNum << " not found. Transaction refused." << endl;
		return false;
	}*/
	Fund fund = (acct->getFunds())[fNum];
	cout << "Transaction History for " << acct->getName() << " ";
	fund.PrintHistory();
	return true;
}

bool Transactions::SliceD(BSTree * tree)
{
	//cout << "reached SliceD" << endl;
	string ID;
	int from = 2;
	int to = from;
	while (trans[to] != ' ')
	{
		to++;
	}
	to -= from;
	if (to != 5) 
	{
		cerr << "ERROR: Transaction (" << trans << ") is invalid.Transaction refused." << endl;
		return false;
	}
	ID = trans.substr(from, to-1);

	string fundNum;
	from = 6;
	fundNum = trans.substr(from, 1);

	string money;
	from = 8;
	to = trans.length() - from;
	money = trans.substr(from, to);

	return D(tree, ID, fundNum, money);
}

//Deposit assets into a fund 
bool Transactions::D(BSTree * tree, string id, string fundNum, string money)
{
	//cout << "reached method D" << endl;
	int ID = stoi(id);
	int fNum = stoi(fundNum);
	int dollars = stoi(money);

	Account *acct = NULL;
	bool found;
	found = tree->Retrieve(ID, acct);
	if (!found)
	{
		cerr << "ERROR: Account " << ID << " not found to deposit assets into a fund. Transaction refused." << endl;
		return false;
	}

	Fund fund = (acct->getFunds())[fNum];
	dollars += fund.getBalance();
	acct->ChangeFundBalance(dollars, fNum);
	acct->LogToFundHistory(trans, fNum);
	/*//a solution not using pointer and getFunds is not const
	Fund fund = (acct->getFunds())[fNum];
	dollars += fund.getBalance();
	(acct->getFunds())[fNum].setBalance(dollars);
	(acct->getFunds())[fNum].LogToHistory(trans);*/
	return true;
}

bool Transactions::SliceW(BSTree * tree)
{
	string ID;
	int from = 2;
	int to = from;
	while (trans[to] != ' ')
	{
		to++;
	}
	to -= from;
	if (to != 5)
	{
		cerr << "ERROR: Transaction (" << trans << ") is invalid.Transaction refused." << endl;
		return false;
	}
	ID = trans.substr(from, to - 1);

	string fundNum;
	from = 6;
	fundNum = trans.substr(from, 1);

	string money;
	from = 8;
	to = trans.length() - from;
	money = trans.substr(from, to);

	return W(tree, ID, fundNum, money);
}

//Withdraw assets from a fund
bool Transactions::W(BSTree * tree, string id, string fundNum, string money)
{
	int ID = stoi(id);
	int fNum = stoi(fundNum);
	int dollars = stoi(money);

	Account *acct = NULL;
	bool found;
	found = tree->Retrieve(ID, acct);
	if (!found)
	{
		cerr << "ERROR: Account " << ID << " not found to withdraw assets from a fund. Transaction refused." << endl;
		return false;
	}

	Fund fund = (acct->getFunds())[fNum];
	int balance = fund.getBalance();
	if (balance < dollars) //not enough balance in this fund
	{
		if (fNum == 0)//linked fund
		{
			int linkedBalance = balance + (acct->getFunds())[1].getBalance();
			if (linkedBalance < dollars)//both balances together do not have enough to withdraw the amount asked
			{
				cerr << "ERROR: " << (acct->getFunds())[fNum].getName() << " does not have enough balance to withdrow $" << dollars << ". Transaction refused." << endl;
				string transFail = trans + " (Failed)";
				acct->LogToFundHistory(transFail, fNum);
				return false;
			}
			else//can withdraw if barrow from the linked fund
			{
				int barrow = dollars - balance;
				acct->ChangeFundBalance(0, fNum);//now has no money and will barrow some to pay the rest
				string transT = "T " + id + "1" + " " + to_string(barrow) + " " + id + fundNum;//log the money transferd (barrowed) to this account
				acct->LogToFundHistory(transT, fNum);
				acct->LogToFundHistory(trans, fNum);
				int newBalance = (acct->getFunds())[1].getBalance() - barrow;
				acct->ChangeFundBalance(newBalance, 1);//barrow form linked Fund
				acct->LogToFundHistory(transT, 1);//log the money transferd from this account to linked fund
				return true;
			}
		}
		else if (fNum == 1)//linked fund
		{
			int linkedBalance = balance + (acct->getFunds())[0].getBalance();
			if (linkedBalance < dollars)
			{
				cerr << "ERROR: " << (acct->getFunds())[fNum].getName() << " does not have enough balance to withdrow $" << dollars << ". Transaction refused." << endl;
				string transFail = trans + " (Failed)";
				acct->LogToFundHistory(transFail, fNum);
				return false;
			}
			else
			{
				int barrow = dollars - balance;
				acct->ChangeFundBalance(0, fNum);//now has no money and will barrow some to pay the rest
				string transT = "T " + id + "0" + " " + to_string(barrow) + " " + id + fundNum;//log the money transferd (barrowed) to this account
				acct->LogToFundHistory(transT, fNum);
				acct->LogToFundHistory(trans, fNum);
				int newBalance = (acct->getFunds())[0].getBalance() - barrow;
				acct->ChangeFundBalance(newBalance, 0);//barrow form linked Fund
				acct->LogToFundHistory(transT, 0);//log the money transferd from this account to linked fund
				return true;
			}
		}
		else if (fNum == 2)//linked fund
		{
			int linkedBalance = balance + (acct->getFunds())[3].getBalance();
			if (linkedBalance < dollars)
			{
				cerr << "ERROR: " << (acct->getFunds())[fNum].getName() << " does not have enough balance to withdrow $" << dollars << ". Transaction refused." << endl;
				string transFail = trans + " (Failed)";
				acct->LogToFundHistory(transFail, fNum);
				return false;
			}
			else
			{
				int barrow = dollars - balance;
				acct->ChangeFundBalance(0, fNum);//now has no money and will barrow some to pay the rest
				string transT = "T " + id + "3" + " " + to_string(barrow) + " " + id + fundNum;//log the money transferd (barrowed) to this account
				acct->LogToFundHistory(transT, fNum);
				acct->LogToFundHistory(trans, fNum);
				int newBalance = (acct->getFunds())[3].getBalance() - barrow;
				acct->ChangeFundBalance(newBalance, 3);//barrow form linked Fund
				acct->LogToFundHistory(transT, 3);//log the money transferd from this account to linked fund
				return true;
			}
		}
		else if (fNum == 3)//linked fund
		{
			int linkedBalance = balance + (acct->getFunds())[2].getBalance();
			if (linkedBalance < dollars)
			{
				cerr << "ERROR: " << (acct->getFunds())[fNum].getName() << " does not have enough balance to withdrow $" << dollars << ". Transaction refused." << endl;
				string transFail = trans + " (Failed)";
				acct->LogToFundHistory(transFail, fNum);
				return false;
			}
			else
			{
				int barrow = dollars - balance;
				acct->ChangeFundBalance(0, fNum);//now has no money and will barrow some to pay the rest
				string transT = "T " + id + "2" + " " + to_string(barrow) + " " + id + fundNum;//log the money transferd (barrowed) to this account
				acct->LogToFundHistory(transT, fNum);
				acct->LogToFundHistory(trans, fNum);
				int newBalance = (acct->getFunds())[2].getBalance() - barrow;
				acct->ChangeFundBalance(newBalance, 2);//barrow form linked Fund
				acct->LogToFundHistory(transT, 2);//log the money transferd from this account to linked fund
				return true;
			}
		}
		else //not a linked fund
		{
			cerr << "ERROR: " << (acct->getFunds())[fNum].getName() << " does not have enough balance to withdrow $" << dollars << ". Transaction refused." << endl;
			string transFail = trans + " (Failed)";
			acct->LogToFundHistory(transFail, fNum);
			return false;
		}
	}
	else //can withdraw
	{
		balance -= dollars;
		acct->ChangeFundBalance(balance, fNum);
		acct->LogToFundHistory(trans, fNum);
		return true;
	}
}

bool Transactions::SliceT(BSTree * tree)
{
	string IDFrom;
	int from = 2;
	int to = from;
	while (trans[to] != ' ')
	{
		to++;
	}
	to -= from;
	if (to != 5)
	{
		cerr << "ERROR: Transaction (" << trans << ") is invalid.Transaction refused." << endl;
		return false;
	}
	IDFrom = trans.substr(from, to - 1);//to -1 to get only the ID w/o fund number

	string fundNumFrom;
	from = 6;
	fundNumFrom = trans.substr(from, 1);

	string money;
	from = 8;
	to = from;
	while (trans[to] != ' ')
	{
		to++;
	}
	to -= from;
	money = trans.substr(from, to);

	string IDTo;
	from += to + 1;
	to = trans.length() - from;
	if (to != 5)//the number for id and function number is not correct
	{
		cerr << "ERROR: Transaction (" << trans << ") is invalid.Transaction refused." << endl;
		return false;
	}
	IDTo = trans.substr(from, to -1);// to -1 because without fund number
	from = trans.length() - 1;
	string fundNumTo = trans.substr(from, 1);

	return T(tree, IDFrom, fundNumFrom, money, IDTo, fundNumTo);
}

//Transfer money from one accountfund to anoter fund from the same or different account
bool Transactions::T(BSTree *tree, string idFrom, string fundNumFrom, string money, string idTo, string fundNumTo)
{
	int IDFrom = stoi(idFrom);
	int fNumFrom = stoi(fundNumFrom);
	int dollars = stoi(money);
	int IDTo = stoi(idTo);
	int fNumTo = stoi(fundNumTo);

	//find both IDes //Error if not found
	//From
	Account *acctFrom = NULL;
	bool foundFrom;
	foundFrom = tree->Retrieve(IDFrom, acctFrom);
	if (!foundFrom)
	{
		cerr << "ERROR: Account " << IDFrom << " not found to Transfer assets from a fund. Transaction refused." << endl;
		return false;
	}

	Fund fundFrom = (acctFrom->getFunds())[fNumFrom];
	int balanceFrom = fundFrom.getBalance();

	//To
	Account *acctTo = NULL;
	bool foundTo;
	foundTo = tree->Retrieve(IDTo, acctTo);
	if (!foundTo)
	{
		cerr << "ERROR: Account " << IDTo << " not found to Transfer assets into a fund. Transaction refused." << endl;
		return false;
	}

	Fund fundTo = (acctTo->getFunds())[fNumTo];
	int balanceTo = fundTo.getBalance();

	//subtract from one and log //Error if not enough
	if (balanceFrom < dollars) //not enough balance in this fund
	{
		if (fNumFrom == 0)//linked fund
		{
			int linkedBalance = balanceFrom + (acctFrom->getFunds())[1].getBalance();
			if (linkedBalance < dollars)//both balances together do not have enough to withdraw the amount asked
			{
				cerr << "ERROR: " << (acctFrom->getFunds())[fNumFrom].getName() << " does not have enough balance to Transfer $" << dollars << ". Transaction refused." << endl;
				string transFail = trans + " (Failed)";
				acctFrom->LogToFundHistory(transFail, fNumFrom);
				return false; // or if need to log T in both accounts then Add the log her and then return!!!!!!!!!!
			}
			else//can withdraw if barrow from the linked fund
			{
				int barrow = dollars - balanceFrom;
				acctFrom->ChangeFundBalance(0, fNumFrom);//now has no money and will barrow some to pay the rest
				string transT = "T " + idFrom + "1" + " " + to_string(barrow) + " " + idFrom + fundNumFrom;//log the money transferd (barrowed) to this account
				acctFrom->LogToFundHistory(transT, fNumFrom);//log the barrowing
				acctFrom->LogToFundHistory(trans, fNumFrom);//log the actual transfer
				int newBalance = (acctFrom->getFunds())[1].getBalance() - barrow;
				acctFrom->ChangeFundBalance(newBalance, 1);//barrow form linked Fund
				acctFrom->LogToFundHistory(transT, 1);//log the money transferd from this account to linked fund
			}
		}
		else if (fNumFrom == 1)//linked fund
		{
			int linkedBalance = balanceFrom + (acctFrom->getFunds())[0].getBalance();
			if (linkedBalance < dollars)//both balances together do not have enough to withdraw the amount asked
			{
				cerr << "ERROR: " << (acctFrom->getFunds())[fNumFrom].getName() << " does not have enough balance to Transfer $" << dollars << ". Transaction refused." << endl;
				string transFail = trans + " (Failed)";
				acctFrom->LogToFundHistory(transFail, fNumFrom);
				return false; // or if need to log T in both accounts then Add the log her and then return!!!!!!!!!!
			}
			else//can withdraw if barrow from the linked fund
			{
				int barrow = dollars - balanceFrom;
				acctFrom->ChangeFundBalance(0, fNumFrom);//now has no money and will barrow some to pay the rest
				string transT = "T " + idFrom + "0" + " " + to_string(barrow) + " " + idFrom + fundNumFrom;//log the money transferd (barrowed) to this account
				acctFrom->LogToFundHistory(transT, fNumFrom);//log the barrowing
				acctFrom->LogToFundHistory(trans, fNumFrom);//log the actual transfer
				int newBalance = (acctFrom->getFunds())[0].getBalance() - barrow;
				acctFrom->ChangeFundBalance(newBalance, 0);//barrow form linked Fund
				acctFrom->LogToFundHistory(transT, 0);//log the money transferd from this account to linked fund
			}
		}
		else if (fNumFrom == 2)//linked fund
		{
			int linkedBalance = balanceFrom + (acctFrom->getFunds())[3].getBalance();
			if (linkedBalance < dollars)//both balances together do not have enough to withdraw the amount asked
			{
				cerr << "ERROR: " << (acctFrom->getFunds())[fNumFrom].getName() << " does not have enough balance to Transfer $" << dollars << ". Transaction refused." << endl;
				string transFail = trans + " (Failed)";
				acctFrom->LogToFundHistory(transFail, fNumFrom);
				return false; // or if need to log T in both accounts then Add the log her and then return!!!!!!!!!!
			}
			else//can withdraw if barrow from the linked fund
			{
				int barrow = dollars - balanceFrom;
				acctFrom->ChangeFundBalance(0, fNumFrom);//now has no money and will barrow some to pay the rest
				string transT = "T " + idFrom + "3" + " " + to_string(barrow) + " " + idFrom + fundNumFrom;//log the money transferd (barrowed) to this account
				acctFrom->LogToFundHistory(transT, fNumFrom);//log the barrowing
				acctFrom->LogToFundHistory(trans, fNumFrom);//log the actual transfer
				int newBalance = (acctFrom->getFunds())[3].getBalance() - barrow;
				acctFrom->ChangeFundBalance(newBalance, 3);//barrow form linked Fund
				acctFrom->LogToFundHistory(transT, 3);//log the money transferd from this account to linked fund
			}
		}
		else if (fNumFrom == 3)//linked fund
		{
			int linkedBalance = balanceFrom + (acctFrom->getFunds())[2].getBalance();
			if (linkedBalance < dollars)//both balances together do not have enough to withdraw the amount asked
			{
				cerr << "ERROR: " << (acctFrom->getFunds())[fNumFrom].getName() << " does not have enough balance to Transfer $" << dollars << ". Transaction refused." << endl;
				string transFail = trans + " (Failed)";
				acctFrom->LogToFundHistory(transFail, fNumFrom);
				return false; // or if need to log T in both accounts then Add the log her and then return!!!!!!!!!!
			}
			else//can withdraw if barrow from the linked fund
			{
				int barrow = dollars - balanceFrom;
				acctFrom->ChangeFundBalance(0, fNumFrom);//now has no money and will barrow some to pay the rest
				string transT = "T " + idFrom + "2" + " " + to_string(barrow) + " " + idFrom + fundNumFrom;//log the money transferd (barrowed) to this account
				acctFrom->LogToFundHistory(transT, fNumFrom);//log the barrowing
				acctFrom->LogToFundHistory(trans, fNumFrom);//log the actual transfer
				int newBalance = (acctFrom->getFunds())[2].getBalance() - barrow;
				acctFrom->ChangeFundBalance(newBalance, 2);//barrow form linked Fund
				acctFrom->LogToFundHistory(transT, 2);//log the money transferd from this account to linked fund
			}
		}
		else //not a linked fund
		{
			cerr << "ERROR: " << (acctFrom->getFunds())[fNumFrom].getName() << " does not have enough balance to transfer $" << dollars << ". Transaction refused." << endl;
			string transFail = trans + " (Failed)";
			acctFrom->LogToFundHistory(transFail, fNumFrom);
			return false;//Log into the To fund as well Maybe!!!!!!!!!!!!!!!!!!!
		}
	}
	else //can withdraw
	{
		balanceFrom -= dollars;
		acctFrom->ChangeFundBalance(balanceFrom, fNumFrom);
		acctFrom->LogToFundHistory(trans, fNumFrom);
	}
	//add to the other and log
	balanceTo += dollars;
	acctTo->ChangeFundBalance(balanceTo, fNumTo);
	acctTo->LogToFundHistory(trans, fNumTo);
	return true;
}

void Transactions::Print()//only for Debuging
{
	cout << trans << endl;
}

istream & operator>>(istream & in, Transactions & transac)//only for Debuging
{
	in >> transac.trans;
	return in;
}
