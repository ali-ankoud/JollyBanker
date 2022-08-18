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
    void readTransactions(const string& fileName);
   
    //will display all of the accounts and balances
    void displayAllBankBalances();
    
    //Transactions that are avaliable to perform
    bool openAccount();
    bool withdrawFunds();
    bool depositeFunds();
    bool transferFunds();
    bool printHistory();




};