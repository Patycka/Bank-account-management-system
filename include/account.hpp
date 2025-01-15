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
  Account(std::string number, std::string name, AccountDAO &accountDao, double balance = 0, double interestRate = 0);

  virtual ~Account() = default;

  friend std::ostream& operator<<(std::ostream& os, const Account& customer);
  void DepositMoney(double amount);
  virtual void WithdrawMoney(double amount);
  void ViewBalance();
  void ViewTransactionHistory();
  void AddTransaction(std::string transaction);
protected:
  double m_balance;
  double m_interestRate;
private:
  std::string m_accountNumber;
  std::string   m_accountHolderName;
  std::string transactionHistory;
  std::string m_type;
  AccountDAO *m_accountDAO; // if reference then account is non copyable
};
} // namespace db
