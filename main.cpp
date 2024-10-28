#include <iostream>
#include "account.hpp"

using namespace std;

int main()
{
    Account account {"01234", "John Doe"};
    cout << account;
    account.WithdrawMoney(100.59);
    cout << account;
    account.DepositMoney(1000);
    cout << account;

    return 0;
}



