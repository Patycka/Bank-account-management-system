#include <ostream>
#include <utility>

#include "account.hpp"
#include "account_dao.hpp"
#include "transaction.hpp"
#include <ctime>

namespace db {
std::ostream& operator<<(std::ostream& os, const Account& account)
{
  os << "Account number: " << account.m_accountNumber << '\n';
  os << "Account holder name: " << account.m_accountHolderName << '\n';
  os << "Balance: " << account.m_balance << '\n';
  os << "Account type: " << account.m_type << '\n';
  os << "Interest rate: " << account.m_interestRate << '\n';

  return os;
}

Account::Account(std::string accountNumber, std::string name, AccountDAO &accountDao, double balance, double interesetRate)
  : m_accountNumber{accountNumber}, m_accountHolderName{std::move(name)}, m_balance {balance}, m_accountDAO {&accountDao}, m_interestRate{interesetRate}
{
}

void Account::DepositMoney(double money)
{
    m_balance += money;
    m_accountDAO->Save(*this);
    // Get the current time
    std::time_t now = std::time(nullptr);
    char buffer[100];
    
    // Format the time as "YYYY-MM-DD HH:MM:SS"
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    TransactionDAO transactionDAO{m_accountDAO->GetSession()};
    Transaction transaction = {"Deposit", money, buffer, m_accountNumber};
    transactionDAO.InsertLog(transaction);
}

void Account::WithdrawMoney(double money)
{
    m_balance -= money;
    m_accountDAO->Save(*this);

    Transaction Transaction{"Withdraw", money, "2021-09-01", m_accountNumber};
}

} // namespace db


