#include "JollyBanker.h"


int main()
{
	JollyBanker bank;
	bank.ReadTransactions();
	bank.ExeTransactions();
	bank.Display();

	system("pause");
     return 0;
}