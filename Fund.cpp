#include "stdafx.h"
#include "Fund.h"


Fund::Fund()
{
	balance = 0;
}


Fund::~Fund()
{

}

bool Fund::addAmount(int amountIn)
{
	balance += amountIn;
	return true;
}

bool Fund::subtractAmount(int amountToSub)
{
	balance -= amountToSub;
	return true;
}

bool Fund::balanceCheck(int amountToSub)
{
	if (balance >= amountToSub)
	{
		return true;
	}
	return false;
}


bool Fund::recordTransaction(Transaction trans)
{
	history.push_back(trans);
	return true;
}

//The printHistory() function checks to see if the size of the vector is equal to 0
//If if is equal to 0, it does not print anything.  If the vector is filled it 
//then cycles through it and prints the transactions
void Fund::printHistory()
{
	if (history.size() == 0)
	{
		return;
	}
	else
	{
		cout << fundName << ": $" << balance << endl;
		for (int i = 0; i < history.size(); i++)
		{
			cout << " " << history[i];
		}
	}
}

//the printHistoryOfFund() function prints the history of a specific fund
void Fund::printHistoryOfFund()
{
	for (int i = 0; i < history.size(); i++)
	{	
		cout << " " << history[i];
	}
}

void Fund::setName(string name)
{
	this->fundName = name;
}

int Fund::getBalance() const
{
	return balance;
}

string Fund::getName() const
{
	return fundName;
}