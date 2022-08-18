#include "Fund.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Account {
    private:
    string firstName, lastName;
    int accountNum{};
    Fund fundsArray[10];

    public:
    //account constructor with parameters
    Account(string cFirstName, string cLastName, int cAccountNum);
   
   //acccount deconstuctor
    ~Account();

    //getter functions 
    string getFirstName();
    string getLastName();
    int getAccountNum();


};