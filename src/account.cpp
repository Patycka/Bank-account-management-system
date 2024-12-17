#include <ostream>
#include <utility>

#include "account.hpp"

namespace db {
std::ostream& operator<<(std::ostream& os, const Account& account)
{
  os << "Account number: " << account.m_accountNumber << '\n';
  os << "Account holder name: " << account.m_accountHolderName << '\n';
  os << "Balance: " << account.m_balance << '\n';

  return os;
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


