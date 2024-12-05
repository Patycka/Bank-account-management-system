#include <iostream>
#include "account.hpp"

using namespace std;

Account::Account(std::string m_accountNumber, std::string m_accountHolderName)
: m_accountNumber{m_accountNumber}, m_accountHolderName{m_accountHolderName}, m_balance{0}
{
}

std::ostream& operator<<(std::ostream& os, const Account& account)
{
    os << "Account number: " << account.m_accountNumber << endl;
    os << "Account holder name: " << account.m_accountHolderName << endl;
    os << "Balance: " << account.m_balance << endl;

    return os;
}

void Account::DepositMoney(double money)
{
    m_balance += money;
}

void Account::WithdrawMoney(double money)
{
    m_balance -= money;
}