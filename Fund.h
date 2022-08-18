#pragma once
#include "Transaction.h"
#include <string>
#include <vector>
#include <iostream>

class Fund
{
public:
	Fund();
	~Fund();

	bool addAmount(int amountIn);
	bool subtractAmount(int amountToSub);
	bool balanceCheck(int amountToSub);
	bool recordTransaction(Transaction trans);
	void printHistoryOfFund();
	void printHistory();
	void setName(string name);
	int getBalance() const;
	string getName() const;


private:
	string fundName;
	int balance = 0;
	vector<Transaction> history;
};
