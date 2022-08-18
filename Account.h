#pragma once
#include "Transaction.h"
#include "Fund.h"
#include <iostream>
#include <string>
using namespace std;

const int FUND_MAX = 10;
const int MONEY_MARKET = 0;
const int PRIME_MONEY_MARKET = 1;
const int LONG_TERM_BOND= 2;
const int SHORT_TERM_BOND = 3;

class Account
{
	friend ostream& operator << (ostream &out, Account &acct);

public:
	Account();
	Account(string firstName, string lastName, int accountID);
	~Account();


	void AddToAccount(int fundNumber, int amount);
	bool MinusFunds(int fundNumber, int amount, Transaction frontTrans);
	void RecordTrans(Transaction trans, int fundNumber);
	void WidthFromSimilarAcct(int primaryFund, int secondaryFund, int amount);
	void PrintHistory();
	void PrintFundHistory(int fundNumber);
	void error(int amount, string firstName, string lastName, int fundNumber);

	int getAccountID() const;
	int getBalance(int fundNumber)const;
	string getFundName(int fundNumber);
	string getFirstName() const;
	string getLastName()const;
	void setFundID(int fundNumber);

private:
	string firstName, lastName;
	int accountID;
	int fundId;
	Fund arrayFund[FUND_MAX];
};