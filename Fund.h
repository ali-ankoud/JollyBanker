#include <iostream>
#include <string>
using namespace std;

class Fund {
private:

int fundBalance =  0;
string nameOfFund;
string fundRecord;


public:
//default constructor
Fund();
//deconstructor
~Fund();

//getters
int getFundBalance();
string getFundName();

//setters
void setFundName (string name);
void setFundBalance(int balance);

//changes fund balances
void withdrawFunds (int amount);
void depositFunds(int amount);
void addFundRecord(const string &record);

//displays fund records
void displayFundRecord();

};