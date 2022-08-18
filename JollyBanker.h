#pragma once
#include<queue>
#include"BSTree.h"
#include"Transaction.h"
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

class JollyBanker
{
public:
	JollyBanker();
	~JollyBanker();
	bool ReadTransactions();
	void ExeTransactions();
	void Display();
	
private:
	queue<Transaction> transactionList;
	BSTree accountList;

};