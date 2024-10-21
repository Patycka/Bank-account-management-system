#include <iostream>
#include "account.hpp"

using namespace std;


void Account::PrintAccount()
{
    cout << "Name: " << this->clientData.name << endl;
    cout << "Number: " << this->clientData.number << endl;
    cout << "Saldo: " << this->clientData.saldo << endl;
}

void Account::CreateNew()
{
}

void Account::Delete()
{

}

void Account::DepositMoney(float money)
{

}

void Account::WithdrawMoney(float money)
{

}
