#include "JollyBanker.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main (int argc, char* argv[]) {
    
    JollyBanker bank;
    
    
    for (int i = 1; i < argc; i++) {
        ofstream output;
        output.open("BankTransOut.txt", ios_base::app);
        output << "The command line argument(s) was " << argv[i] << endl;
        string fileName = argv[i];
        bank.readTransactions(fileName);
    }
    
   

}