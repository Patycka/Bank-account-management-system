#pragma once
#include <cstdint>

#include <iosfwd>
#include <string>

namespace db {
class AccountDAO;

class Account {
public:
  friend class AccountDAO;

  friend std::ostream& operator<<(std::ostream& os, const Account& customer);
  void DepositMoney(double money);
  void WithdrawMoney(double money);

private:
  Account(std::string number, std::string name);

  std::string m_accountNumber;
  std::string   m_accountHolderName;
  double m_balance;
};
} // namespace db
