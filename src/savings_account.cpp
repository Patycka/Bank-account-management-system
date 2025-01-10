#include "savings_account.hpp"
#include "account_dao.hpp"

SavingsAccount::SavingsAccount(std::string number, std::string name, db::AccountDAO &accountDao, double interestRate)
    : db::Account{number, name, accountDao, interestRate}
{
}