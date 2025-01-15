#include "savings_account.hpp"
#include "account_dao.hpp"

SavingsAccount::SavingsAccount(std::string number, std::string name, db::AccountDAO &accountDao, double interestRate, double balance)
    : db::Account{number, name, accountDao, balance, interestRate}
{
}

void SavingsAccount::ApplyInterest()
{
    m_balance += m_balance * m_interestRate;
}