#include <iostream>
#include "account.hpp"

using namespace std;

int main()
{
    int choice = 0;

    Account account("dane.txt");

    cout << "Bank database" << endl;
    cout << "1. Create account" << endl;

    cout << "Choose 1-6" << endl;
    cin >> choice;
    cin.ignore();

    switch(choice)
    {
    case 1:
        //account.CreateNew();
        //account.CreateNew();
        //account.CreateNew();
        //account.SearchByName("patrycja");
        account.PrintAccount();
        account = Account::SearchAccountByName("patrycja");
        account.PrintAccount();
        break;
    default:
        cout << "Fault" << endl;
    }

    return 0;
}



