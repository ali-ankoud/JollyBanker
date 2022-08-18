#include "BSTree.h"
#include <fstream>
#include <queue>
#include <string>

class JollyBanker {
    private:
    //queue where the transactions are held to be processed
    queue <string> transactionsQueue;
    BSTree accountTree;

    public:
    JollyBanker();
    ~JollyBanker();

    //reads in file of transactions that is given
    void readTransactions(const string &fileName);
   
    //will display all of the accounts and balances
    void displayAllBankBalances();
    
    //Transactions that are avaliable to perform
    bool openAccount(const string &transaction);
    bool withdrawFunds(const string &transaction);
    bool depositFunds(const string &transaction);
    bool transferFunds(const string &transaction);
    bool printHistory(const string &transaction);




};