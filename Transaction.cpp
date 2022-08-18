#include "stdafx.h"
#include <iostream>
#include "Transaction.h"


Transaction::Transaction()
{

}


Transaction::~Transaction()
{

}

Transaction::Transaction(char type, string firstName, string lastName, int accountNumber)
{
	this->transactionType = type;
	this->firstName = firstName;
	this->lastName = lastName;
	this->accountID = accountNumber;
}
Transaction::Transaction(char type, int accountNumber, int fundNumber, int amount)
{
	this->transactionType = type;
	this->accountID = accountNumber;
	this->fundID = fundNumber;
	this->amount = amount;
}

Transaction::Transaction(char type, int accountNumber, int fundNumber, string failString, int amount)
{
	this->transactionType = type;
	this->accountID = accountNumber;
	this->fundID = fundNumber;
	this->amount = amount;
	this->fail = failString;
}

Transaction::Transaction(char type, int accountNumber, int fundNumber, int amount, int transferAccountNumber, int transferFundNumber)
{
	this->transactionType = type;
	this->accountID = accountNumber;
	this->fundID = fundNumber;
	this->amount = amount;
	this->transferAccountID = transferAccountNumber;
	this->transferFundID = transferFundNumber;
}

Transaction::Transaction(char type, int accountNumber, int fundNumber, int amount, int transferAccountNumber, int transferFundNumber, string failString)
{
	this->transactionType = type;
	this->accountID = accountNumber;
	this->fundID = fundNumber;
	this->amount = amount;
	this->transferAccountID = transferAccountNumber;
	this->transferFundID = transferFundNumber;
	this->fail = failString;
}


Transaction::Transaction(char type, int accountNumber)
{
	this->transactionType = type;
	this->accountID = accountNumber;
}

Transaction::Transaction(char type, int accountNumber, int fundNumber)
{
	this->transactionType = type;
	this->accountID = accountNumber;
	this->fundID = fundNumber;

}
//Checks if the string fail is empty, if it is not empty the transaction failed to process
bool Transaction::isFailed()
{
	if (fail.empty()) 
	{
		return true;
	}
	return false;
}

char Transaction::getTransactionType() const
{
	return transactionType;
}

string Transaction::getFirstName() const
{
	return firstName;
}

string Transaction::getLastName() const
{
	return lastName;
}

int Transaction::getAccountID() const
{
	return accountID;
}

int Transaction::getAmount() const
{
	return amount;
}

int Transaction::getFundID() const
{
	return fundID;
}

int Transaction::getTransferAccountID() const
{
	return transferAccountID;
}

int Transaction::getTransferFundID() const
{
	return transferFundID;
}

//This overloaded operater check to see if the string fail is empty, if it is empty
//there is a "failed" string attached to the end of the output
ostream & operator<<(ostream & out, const Transaction & trans)
{
	if (trans.fail.empty())
	{
		if (trans.getTransactionType() == 'D' || trans.getTransactionType() == 'd' || trans.getTransactionType() == 'W' || trans.getTransactionType() == 'w')
		{
			out << " " << trans.getTransactionType() << " " << trans.getAccountID() << trans.getFundID() << " " << trans.getAmount();
		}
		else if (trans.getTransactionType() == 'T' || trans.getTransactionType() == 't')
		{
			out << " " << trans.getTransactionType() << " " << trans.getAccountID() << trans.getFundID() << " " << trans.getAmount() << " " << trans.getTransferAccountID() << trans.getTransferFundID();
		}
		else
		{

		}
	}
	else
	{
		if (trans.getTransactionType() == 'D' || trans.getTransactionType() == 'd' || trans.getTransactionType() == 'W' || trans.getTransactionType() == 'w')
		{
			out << " " << trans.getTransactionType() << " " << trans.getAccountID() << trans.getFundID() << " " << trans.getAmount() << " (FAILED)";
		}
		else if (trans.getTransactionType() == 'T' || trans.getTransactionType() == 't')
		{
			out << " " << trans.getTransactionType() << " " << trans.getAccountID() << trans.getFundID() << " " << trans.getAmount() << " " << trans.getTransferAccountID() << trans.getTransferFundID() << "(FAILED)";
		}
		else
		{

		}

	}
	return out << endl;

}