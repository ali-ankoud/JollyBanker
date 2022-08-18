#include "stdafx.h"
#include "Account.h"

Account::Account()
{

}

//The constructor creates an account with a first and last anme, account ID(Number)
//and gives names to the corresponding funds 
Account::Account(string firstName, string lastName, int accountID)
{
	this->firstName = firstName;
	this->lastName = lastName;
	this->accountID = accountID;
	string fundNames[] = { "Money Market", "Prime Money Market","Long-Term Bond", "Short-Term Bond","500 Index Fund", "Capital Value Fund","Growth Equity Fund", "Growth Index Fund","Value Fund", "Value Stock Index" };
	for (int i = 0; i < 10; i < i++)
	{
		arrayFund[i].setName(fundNames[i]);
	}
}

int Account::getAccountID() const
{
	return accountID;
}

void Account::AddToAccount(int fundNumber, int amount)
{
	arrayFund[fundNumber].addAmount(amount);

}

//The WidthFromSimilarAcct() function is used during the widthdrawl of two linked accounts.  
void Account::WidthFromSimilarAcct(int primaryFund, int secondaryFund, int amount)
{
	if (((arrayFund[primaryFund].getBalance() + arrayFund[secondaryFund].getBalance()) >= amount))//there is enough money in both accounts
	{
		int balAvailable = arrayFund[primaryFund].getBalance();
		arrayFund[primaryFund].subtractAmount(balAvailable);
		Transaction addToHistory('W', getAccountID(), primaryFund, balAvailable);
		arrayFund[primaryFund].recordTransaction(addToHistory);
		amount = amount - balAvailable;
		arrayFund[secondaryFund].subtractAmount(amount);
		Transaction addToHistory2('W', getAccountID(), secondaryFund, amount);
		arrayFund[secondaryFund].recordTransaction(addToHistory2);
	}
	else
	{
		int balAvailable = arrayFund[primaryFund].getBalance();//get balance from primary fund(inital fund)
		if (balAvailable > amount)
		{
			arrayFund[primaryFund].subtractAmount(balAvailable);//set balance to 0
			Transaction addToHistory('W', getAccountID(), primaryFund, balAvailable);//create transactoin to record
			arrayFund[primaryFund].recordTransaction(addToHistory);//add to history
			amount = amount - balAvailable;
		}

		if (arrayFund[secondaryFund].balanceCheck(amount))//check aother account
		{
			arrayFund[secondaryFund].subtractAmount(amount);//Take from other Account
			Transaction addToHistory('W', getAccountID(), secondaryFund, amount);//create transaction
			arrayFund[secondaryFund].recordTransaction(addToHistory);//record transaction
		}
		else
		{
			cerr << "ERROR: Not Enought Funds to withdraw " << amount << " " << "from " << getFirstName() << " " << getLastName() << " " << getFundName(secondaryFund) << endl;
			Transaction addToHistory('W', getAccountID(), secondaryFund, "Failed", amount);//create transactoin to record
			arrayFund[secondaryFund].recordTransaction(addToHistory);//add to history
		}
	}
}

//The MinusFunds function is used in the widthdrawl of a money from individual funds.
//First the function checks if the parameter fundNumber is any of the special funds (index 0-4)
//If they are not, they proceed to trying to subtract from the balance available.  If they are part of the speical linked index
//the fucnction first checks if it can widthdrwal from the primary fund index.  If it cannot, it then checks if the amount subtracted
//is less than the total of the combied of two funds.  If it cannot widthdrawl from 2 funds it shoots out and error. 
bool Account::MinusFunds(int fundNumber, int amount, Transaction frontTrans)
{
	if (fundNumber == MONEY_MARKET || fundNumber == PRIME_MONEY_MARKET || fundNumber == LONG_TERM_BOND || fundNumber == SHORT_TERM_BOND)
	{
		if (fundNumber == MONEY_MARKET || fundNumber == PRIME_MONEY_MARKET)
		{
			if (arrayFund[fundNumber].balanceCheck(amount))
			{
				arrayFund[fundNumber].subtractAmount(amount);
				arrayFund[fundNumber].recordTransaction(frontTrans);
				return true;
			}
			else if(((arrayFund[MONEY_MARKET].getBalance() + arrayFund[PRIME_MONEY_MARKET].getBalance()) >= amount))
			{
				if (fundNumber == MONEY_MARKET)
				{
					WidthFromSimilarAcct(MONEY_MARKET, PRIME_MONEY_MARKET, amount);
				}
				else
				{
					WidthFromSimilarAcct(PRIME_MONEY_MARKET, MONEY_MARKET, amount);
				}
			}
			else
			{
				error(amount, getFirstName(), getLastName(), fundNumber);
				if (fundNumber == MONEY_MARKET)
				{
					WidthFromSimilarAcct(MONEY_MARKET, PRIME_MONEY_MARKET, amount);
				}
				else
				{
					WidthFromSimilarAcct(PRIME_MONEY_MARKET, MONEY_MARKET, amount);
				}
				return false;
			}
		}
		else if (fundNumber == LONG_TERM_BOND|| fundNumber == SHORT_TERM_BOND)
		{
			if (arrayFund[fundNumber].balanceCheck(amount))
			{
				arrayFund[fundNumber].subtractAmount(amount);
				arrayFund[fundNumber].recordTransaction(frontTrans);
				return true;
			}
			else if (((arrayFund[LONG_TERM_BOND].getBalance() + arrayFund[SHORT_TERM_BOND].getBalance()) >= amount))
			{
				if (fundNumber == LONG_TERM_BOND)
				{
				WidthFromSimilarAcct(LONG_TERM_BOND, SHORT_TERM_BOND, amount);
				}
				else
				{
					WidthFromSimilarAcct(SHORT_TERM_BOND, LONG_TERM_BOND, amount);
				}
			}
			else
			{
				error(amount, getFirstName(), getLastName(), fundNumber);
				if (fundNumber == LONG_TERM_BOND)
				{
					WidthFromSimilarAcct(LONG_TERM_BOND, SHORT_TERM_BOND, amount);
				}
				else
				{
					WidthFromSimilarAcct(SHORT_TERM_BOND, LONG_TERM_BOND, amount);
				}
				return false;
			}
		}
	}
	else
	{
		if (arrayFund[fundNumber].balanceCheck(amount))
		{
			arrayFund[fundNumber].subtractAmount(amount);
			arrayFund[fundNumber].recordTransaction(frontTrans);
			return true;
		}
		else
		{	
			error(amount, getFirstName(), getLastName(), fundNumber);
			return false;
		}
	}
}

void Account::error(int amount, string firstName, string lastName, int fundNumber)
{
	cerr << "ERROR: Not Enought Funds to withdraw " << amount << " " << "from " << firstName << " " << lastName << " " << getFundName(fundNumber) << endl;
	Transaction addToHistory('W', getAccountID(), fundNumber, "Failed", amount);//create transactoin to record
	arrayFund[fundNumber].recordTransaction(addToHistory);//add to history
}

void Account::RecordTrans(Transaction trans, int fundNumber)
{
	arrayFund[fundNumber].recordTransaction(trans);
}

void Account::PrintHistory()
{
	cout << "Transaction History for " << firstName << " " << lastName << " " << "By Fund."<< endl;
	for (int i = 0; i < 10; i++)
	{
		arrayFund[i].printHistory();
	}
}

void Account::PrintFundHistory(int fundID)
{
	cout << "Transaction History for " << firstName << " " << lastName << " " << getFundName(fundID) << " $" << getBalance(fundID) <<  endl;
	arrayFund[fundID].printHistoryOfFund();
}

void Account::setFundID(int fundNumber)
{
	this->fundId = fundNumber;
}



int Account::getBalance(int fundNumber)const
{
	return arrayFund[fundNumber].getBalance();
}

string Account::getFundName(int fundNumber)
{
	return arrayFund[fundNumber].getName();
}

string Account::getFirstName() const
{
	return firstName;
}

string Account::getLastName() const
{
	return lastName;
}

ostream & operator<<(ostream & out, Account & account)
{
	out << account.getFirstName() << " " << account.getLastName() << " ID: " << account.getAccountID() << endl;
	for (int i = 0; i < 10; i++)
	{
		out << " " << account.getFundName(i) << " :$" << account.getBalance(i);
		out << endl;
	}
	
	return out;

}

Account::~Account()
{

}