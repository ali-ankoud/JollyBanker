#pragma once
#include <string>
using namespace std;

class Transaction
{
	friend ostream & operator<<(ostream &out, const Transaction &trans);
public:
	Transaction();
	~Transaction();
	Transaction(char type, string firstName, string lastName, int accountNumber);
	Transaction(char type, int accountNumber, int fundNumber, int amount);
	Transaction(char type, int accountNumber, int fundNumber, int amount, int transferAccountNumber, int transferFundNumber);
	Transaction(char type, int accountNumber);
	Transaction(char type, int accountNumber, int fundNumber);

	//These Construtors create a transaction that failed to process
	Transaction(char type, int accountNumber, int fundNumber, int amount, int transferAccountNumber, int transferFundNumber, string failString);
	Transaction(char type, int accountNumber, int fundNumber, string fail, int amount);

	bool isFailed();
	char getTransactionType() const;
	string getFirstName() const;
	string getLastName() const;
	int getAccountID() const;
	int getFundID() const;
	int getTransferAccountID() const;
	int getTransferFundID() const;
	int getAmount() const;


private:
	char transactionType;
	string firstName;
	string lastName;
	string fail;
	int accountID, fundID, transferAccountID, transferFundID, amount;
};
