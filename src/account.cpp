#include <ostream>
#include <utility>

#include "account.hpp"

namespace db {
std::ostream& operator<<(std::ostream& os, const Account& account)
{
  return os << "Account{"
            << "number: " << account.m_accountNumber << ", name: " << account.m_accountHolderName << "}";
}

Account::Account(std::string accountNumber, std::string name)
  : m_accountNumber{accountNumber}, m_accountHolderName{std::move(name)}, m_balance {0}
{
}

void Account::DepositMoney(double money)
{
    m_balance += money;
}

void Account::WithdrawMoney(double money)
{
    m_balance -= money;
}

} // namespace db

// Account::Account(std::string m_accountNumber, std::string m_accountHolderName)
// : m_accountNumber{m_accountNumber}, m_accountHolderName{m_accountHolderName}, m_balance{0}
// {
// }

// std::ostream& operator<<(std::ostream& os, const Account& account)
// {
//     os << "Account number: " << account.m_accountNumber << endl;
//     os << "Account holder name: " << account.m_accountHolderName << endl;
//     os << "Balance: " << account.m_balance << endl;

//     return os;
// }

