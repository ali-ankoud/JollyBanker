#include <iostream>
#include <string>
using namespace std;

class Fund {
private:

public:
//default constructor
Fund();
//deconstructor
~Fund();


private:
string fundName;
string fundHistory;
int fundBalance = 0;


};