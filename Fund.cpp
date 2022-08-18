#include "Fund.h"
#include <string>
#include <fstream>
#include <utility>
using namespace std;

//constructor
Fund::Fund(){
    fundBalance = 0;
}

//deconstructor
Fund::~Fund(){

}

//getters
int Fund::getFundBalance() {
    return fundBalance;
}
string Fund::getFundName(){
    return nameOfFund;
}

//setters
void Fund::setFundBalance(int balance){
    fundBalance = balance;
    
}

void Fund::setFundName(string name){
    nameOfFund = move(name);
}

void Fund::depositFunds(int amount){
    fundBalance += amount;
}

void Fund::withdrawFunds(int amount){
    fundBalance -= amount;
}

void Fund :: addFundRecord(const string &record){
    fundRecord += (record + '\n');
}

void Fund::displayFundRecord(){
    ofstream outfile;
    outfile.open("BankTransOut.txt", ios_base::app);
    outfile << nameOfFund << ": $" << fundBalance << endl;
    outfile << fundRecord;
}