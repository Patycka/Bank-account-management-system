#pragma once
#include <cstdint>

#include <iosfwd>
#include <string>

// namespace db {
// class CustomerDAO;

// class Customer {
// public:
//   friend class CustomerDAO;

//   friend std::ostream& operator<<(std::ostream& os, const Customer& customer);

// private:
//   Customer(std::uint64_t id, std::string name);

//   std::uint64_t m_id;
//   std::string   m_name;
// };
// } // namespace db

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



// class Account
// {
// private:
//     std::string m_accountNumber;
//     std::string m_accountHolderName;
//     double m_balance;

// public:
//     Account(std::string m_accountNumber, std::string m_accountHolderName);
//     friend std::ostream& operator<<(std::ostream& os, const Account& account);


// };