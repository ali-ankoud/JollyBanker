// Ali Ankoud

#include "stdafx.h"
#include "JollyBanker.h"
#include "Transaction.h"
#include "Account.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <queue>


JollyBanker::JollyBanker()
{
}


JollyBanker::~JollyBanker()
{
}

//The ReadTransaction fucntion, reads the input file and creates the 
//appropriate transaction and places them into the queue.
bool JollyBanker::ReadTransactions()
{
	ifstream in("BankTransIn.txt");
	string readLine;
	if (!in)
	{
		cout << "Cannot Open!" << endl;
	}

	while (!in.eof())
	{
		getline(in, readLine);
		if (readLine.empty())
		{
			break;
		}
		istringstream parseLine(readLine);
		char transactionType;
		parseLine >> transactionType;
	
		if (transactionType == 'O' || transactionType == 'o')
		{
			string lastName, firstName;
			int accountID;
			parseLine >> firstName >> lastName >> accountID;
			Transaction addToQueue(transactionType, firstName, lastName, accountID);
			transactionList.push(addToQueue);

		}
		else if (transactionType == 'W' || transactionType == 'w' || transactionType == 'D' || transactionType == 'd')
		{
			int accountID, fundID, amount;
			parseLine >> accountID >> amount;
			fundID = accountID % 10;
			accountID = accountID / 10;
			Transaction addToQueue(transactionType, accountID, fundID, amount);
			transactionList.push(addToQueue);
		}
		else if (transactionType == 'T'|| transactionType == 't')
		{
			int accountID, fundID, amount, trasnferAccountID, transferFundID;
			parseLine >> accountID >> amount >> trasnferAccountID;
			fundID = accountID % 10;
			accountID = accountID / 10;
			transferFundID = trasnferAccountID % 10;
			trasnferAccountID = trasnferAccountID / 10;
			Transaction addToQueue(transactionType, accountID, fundID, amount, trasnferAccountID, transferFundID);
			transactionList.push(addToQueue);
		}
		else if(transactionType == 'H' || transactionType == 'h')
		{
			int accountID, fundID;
			int integerTest;
			int length = 1;
			parseLine >> accountID;
			Transaction addToQueue(transactionType, accountID);
			transactionList.push(addToQueue);
		}
		else
		{
			cout << "ERROR!" << endl;
		}
	}
	return false;
}

//THe ExeTransaction pops off transactions from the queue.  The first character of the transaction
//dictates the action taken on the it.  Each section of the if/then statements generates an 
//Account pointer which is retrived from the Binary Seach Tree and manipulates the data. 
void JollyBanker::ExeTransactions()
{
	while (!transactionList.empty())
	{
		Transaction frontTrans = transactionList.front();

		if (frontTrans.getTransactionType() == 'O' || frontTrans.getTransactionType() == 'o')
		{
			Account * account = new Account(frontTrans.getFirstName(), frontTrans.getLastName(), frontTrans.getAccountID());
			accountList.Insert(account);
		}
		else if (frontTrans.getTransactionType() == 'D' || frontTrans.getTransactionType() == 'd')
		{
			int accountNumber = frontTrans.getAccountID();
			int fundNumber = frontTrans.getFundID();
			int amountToAdd = frontTrans.getAmount();
			Account *account;
			if (accountList.Retrieve(accountNumber, account))
			{
				account->AddToAccount(fundNumber, amountToAdd);
				account->RecordTrans(frontTrans, fundNumber);
			}

		}
		else if (frontTrans.getTransactionType() == 'W' || frontTrans.getTransactionType() == 'w')
		{
			int accountNumber = frontTrans.getAccountID();
			int fundNumber = frontTrans.getFundID();
			int amountToSubtract = frontTrans.getAmount();
			Account *account;
			if (accountList.Retrieve(accountNumber, account))
			{
				account->MinusFunds(fundNumber, amountToSubtract, frontTrans);
			}

		}
		else if (frontTrans.getTransactionType() == 'T' || frontTrans.getTransactionType() == 'T')
		{
			int accountNumber = frontTrans.getAccountID();
			int transferAcctNum = frontTrans.getTransferAccountID();
			int fundNumber = frontTrans.getFundID();
			int transferFundNum = frontTrans.getTransferFundID();
			int amountToSub = frontTrans.getAmount();
			Account *to, *from;
			if(accountList.Retrieve(accountNumber, to) && accountList.Retrieve(transferAcctNum, from))
			{
				if (to->MinusFunds(fundNumber, amountToSub, frontTrans))
				{
					from->AddToAccount(transferFundNum, amountToSub);
					from->RecordTrans(frontTrans, transferFundNum);
				}
				else
				{
					cerr << "ERROR: Not Enought Funds to Transer  " << amountToSub << " " << "from " << from->getAccountID() << fundNumber << " to " << to->getAccountID() << transferFundNum << endl;
					Transaction addToHistory('T', accountNumber, fundNumber, amountToSub, transferAcctNum, transferFundNum, "(Failed)");
					from->RecordTrans(addToHistory, transferFundNum);
				}
			}

		}
		else if (frontTrans.getTransactionType() == 'H' || frontTrans.getTransactionType() == 'h')
		{
			if(frontTrans.getAccountID() >= 10000 && frontTrans.getAccountID() <= 99999)//5 digits = account number + fund
			{
				Account *account;
				int fundNumPrt = frontTrans.getAccountID() % 10;
				int acctNumSearch = frontTrans.getAccountID() / 10;
				if (accountList.Retrieve(acctNumSearch, account))
				{
					account->PrintFundHistory(fundNumPrt);
					cout << endl;
				}
			}
			else if(frontTrans.getAccountID() >= 1000 && frontTrans.getAccountID() <= 9999)//4 digits = account number
			{
				Account *account;
				int acctNumSearch = frontTrans.getAccountID();
				if (accountList.Retrieve(acctNumSearch, account))
				{
					account->PrintHistory();
					cout << endl;
				}
			}
		}
		transactionList.pop();
	}
}

void JollyBanker::Display()
{
	cout << endl;
	cout << "Processing Done. Final Balances" << endl;
	accountList.Display();
}