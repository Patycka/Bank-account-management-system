#include "checking_account.hpp"
#include "account_dao.hpp"

CheckingAccount::CheckingAccount(std::string number, std::string name, db::AccountDAO &accountDao, double interestRate)
    : db::Account{number, name, accountDao, interestRate}
{
    m_type = "Checking";
}

void CheckingAccount::WithdrawMoney(double money)
{
    if (m_balance - money < 0)
    {
        std::cerr << "Insufficient funds\n";
        return;
    }
    Account::WithdrawMoney(money);
}