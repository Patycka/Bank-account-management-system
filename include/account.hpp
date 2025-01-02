#pragma once
#include <cstdint>

#include <iosfwd>
#include <string>

////////////////////////////////////////////////////////////////////////
// Base class for different types of accounts
////////////////////////////////////////////////////////////////////////

namespace db {
class AccountDAO;

class Account {
public:
  friend class AccountDAO;

  friend std::ostream& operator<<(std::ostream& os, const Account& customer);
  void DepositMoney(double amount);
  void WithdrawMoney(double amount);
  void ViewBalance();
  void ViewTransactionHistory();
  void AddTransaction(std::string transaction);

private:
  Account(std::string number, std::string name, AccountDAO &accountDao, double balance = 0);

  std::string m_accountNumber;
  std::string   m_accountHolderName;
  double m_balance;
  std::string transactionHistory;
  AccountDAO *m_accountDAO; // if reference then account is non copyable
};
} // namespace db
