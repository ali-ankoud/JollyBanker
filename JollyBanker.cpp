#include "JollyBanker.h"
#include <queue>
#include <sstream>
#include <fstream>

//defualt constructor
JollyBanker::JollyBanker(){

}

//deconstructor
JollyBanker::~JollyBanker(){
}

//this will pop transactions onto a queue and read out the transactions 
//from the queue as well
void JollyBanker::readTransactions(const string &fileName){

    ifstream input(fileName);
    string line;

    //will strore each line into a queue
    while (getline(input, line)){
        transactionsQueue.push(line);
    }

    //string that will be set to transaction
    string transaction;

    while (!transactionsQueue.empty()){
        transaction = transactionsQueue.front();
        transactionsQueue.pop();

        //will read the frist character to call the approrpriate function

        if (transaction[0] == 'O' || transaction[0] == 'o'){
            openAccount(transaction);
        }
           if (transaction[0] == 'D' || transaction[0] == 'd'){
            depositFunds(transaction);
        }
        if (transaction[0] == 'W' || transaction[0] == 'w'){
            withdrawFunds(transaction);
        }

          if (transaction[0] == 'T' || transaction[0] == 't'){
            transferFunds(transaction);
        }

         if (transaction[0] == 'H' || transaction[0] == 'h'){
            printHistory(transaction);
        }
    }
    //Note that queue should be empty at this point

}

void JollyBanker::displayAllBankBalances(){
    ofstream outfile;
    outfile.open("BankTransOut.txt", ios_base::app);
    outfile << "\nProccess is complete. Final Balances" << endl;

    //Display the BST
    accountTree.display();

}

//will run the functionof opening a new account
bool JollyBanker::openAccount(const string& transaction) {
    string firstName;
    string lastName;
    int accountNum = 0;
    string word;
    queue<string> tempQueue;

    ofstream outfile;
    outfile.open("BankTransOut.txt", ios_base::app);

    istringstream iss(transaction, istringstream::in);

    while (iss >> word) {
        tempQueue.push(word);
    }

    // this will parse a given string
    tempQueue.pop();
    lastName = tempQueue.front();
    tempQueue.pop();
    firstName = tempQueue.front();
    tempQueue.pop();
    accountNum = stoi(tempQueue.front());
    tempQueue.pop();

    Account* current = nullptr;
    if (accountTree.retrieve(accountNum, current)) {
        // will output an error message
        outfile << "ERROR!! This Account " << accountNum << 
        " is already open. Transaction refused." << endl;
        return false;
    }

    // making a new account
    auto* newAccount = new Account(firstName, lastName, accountNum);

    // Add account to BST
    BSTree.insert(newAccount);

    return false;
}

//will perfrom the withdrawing actions
bool JollyBanker::withdrawFunds(const string &transaction){
    
    string word;
    int currentFund = 0;
    int accountNum =0;
    int withdrawAmount=0;
    queue<string> tempQueue;
    ofstream outfile;
    outfile.open("BankTransOut.txt", ios_base::app);
    istringstream iss(transaction, istringstream::in);

    while (iss >> word){
        tempQueue.push(word);    
    }

     // parse given string
    tempQueue.pop();
    word = tempQueue.front();
    currentFund = stoi(word.substr(4, 1));
    word.pop_back();
    accountNum = stoi(word);
    tempQueue.pop();
    withdrawAmount = stoi(tempQueue.front());
    tempQueue.pop();
    // All variables are set

    // return false if account does not exist
    Account* current = nullptr;
    if (!accountTree.retrieve(accountNum, current)) {
        // Output Error Message
        outfile << "ERROR: withdraw unsucessful, this account does not exist" << endl;
        return false;
    }

    // return false if insufficient funds
    if (!current->subAccWithdraw(currentFund, withdrawAmount)) {
        current->writeAccountRecord(transaction + " (Failed)", currentFund);
        return false;
    }

    // log to account record
    current->writeAccountRecord(transaction, currentFund);
    return true;
}


//This function will perform the deposite actions
bool JollyBanker::depositFunds(const string &transaction){
    
    string word;
    int currentFund = 0;
    int accountNum = 0;
    int depositAmount = 0;
    queue<string> tempQueue;

    ofstream outfile;
    outfile.open("BankTransout.txt", ios_base::app);
        istringstream iss(transaction, istringstream::in);

    while (iss >> word) {
        tempQueue.push(word);
    }

    // parse given string
    tempQueue.pop();
    word = tempQueue.front();
    currentFund = stoi(word.substr(4, 1));
    word.pop_back();
    accountNum = stoi(word);
    tempQueue.pop();
    depositAmount = stoi(tempQueue.front());
    tempQueue.pop();

    Account* current = nullptr;
    if (!accountTree.retrieve(accountNum, current)) {
        // Output Error Message
        outfile << "Deposit unsucessful, this account does not exist" << endl;
        return false;
    }

    // deposit into account and record
    current->subAccDeposit(currentFund, depositAmount);
    current->writeAccountRecord(transaction, currentFund);
    return false;
}

//will transfer funds from on account to another
bool JollyBanker:: transferFunds(const string &transaction){
    int withdrawFund = 0;
    int depositFund = 0;
    int withdrawAccount = 0;
    int depositAccount = 0;
    int amount = 0;
    string word;
    queue<string> tempQueue;

    ofstream outfile;
    outfile.open("BankTransOut.txt" , ios_base::app);
    istringstream iss(transaction, istringstream::in);

        while (iss >> word) {
        tempQueue.push(word);
    }

    tempQueue.pop();

    // parse given string starting with "fromAccount"
    word = tempQueue.front();
    withdrawFund = stoi(word.substr(4, 1));
    word.pop_back();
    withdrawAccount = stoi(word);
    tempQueue.pop();
    // Here we get the amount
    amount = stoi(tempQueue.front());
    tempQueue.pop();
    // Getting "depositAccount" fund infomation
    word = tempQueue.front();
    depositFund = stoi(word.substr(4, 1));
    word.pop_back();
    depositAccount = stoi(word);
    tempQueue.pop();

    // Get pointer to withdrawAccount
    Account* fromAccountPtr = nullptr;
    if (!accountTree.retrieve(withdrawAccount, fromAccountPtr)) {
        // Output Error Message
        outfile << "ERROR!! Account not found " << withdrawAccount
                << " Transfer cancelled." << endl;
        return false;
    }

    // Get pointer to depositAccount
    Account* toAccountPtr = nullptr;
    if (!accountTree.retrieve(depositAccount, toAccountPtr)) {
        // Output Error Message
        outfile << "ERROR!! Account not found " << depositAccount
                << " Transfer cancelled." << endl;
        return false;
    }

    // will try to withdraw, and will deposit if successful
    if (fromAccountPtr->subAccWithdraw(withdrawFund, amount)) {
        toAccountPtr->subAccDeposit(depositFund, amount);
        fromAccountPtr->writeAccountRecord(transaction, withdrawFund);
        return true;
    }

    return false;

}

//will print out the account history
bool JollyBanker::printHistory(const string &transaction){

    int currentFund = -1;
    int accountNum = 0;
    string word;
    queue<string>tempQueue;
    ofstream outfile;

    outfile.open("BankTransOut.txt",ios_base::app);
    istringstream iss(transaction, istringstream::in);

     while (iss >> word) {
        tempQueue.push(word);
    }

    // parse given string
    tempQueue.pop();
    word = tempQueue.front();
    // if length is 5, we are showing history for 1 fund only, get fund#
    if (word.length() == 5) {
        currentFund = stoi(word.substr(4, 1));
        word.pop_back();
    }
    accountNum = stoi(word);
    tempQueue.pop();

    // get pointer to account
    Account* current = nullptr;
    if (!accountTree.retrieve(accountNum, current)) {
        // Output Error Message
        outfile << "Can't display, this account does not exist" << endl;
        return false;
    }

    // call function to display all funds or 1 fund
    if (currentFund == -1) {
        // Display everything
        current->displayAccountRecord();
    } else {
        outfile << "Displaying Transaction History for "
                << current->getLastName() << " " << current->getFirstName()
                << "'s ";
        outfile.close();
        current->displaySubAccountRecord(fund);
    }
    return true;


}