#pragma once
#include <optional>

#include <Poco/Data/Session.h>

#include "account.hpp"

// namespace db {
// class CustomerDAO {
// public:
//   explicit CustomerDAO(Poco::Data::Session& session);

//   std::optional<Customer> createCustomer(std::string name);

//   std::optional<Customer> readCustomer(std::uint64_t id);

//   bool updateCustomer(Customer& customer, std::string newName);

//   bool deleteCustomer(Customer& customer);

// private:
//   static std::uint64_t nextId();

//   Poco::Data::Session& m_session;
// };
// } // namespace db

namespace db {
class AccountDAO {
public:
  explicit AccountDAO(Poco::Data::Session& session);

  std::optional<Account> CreateAccount(std::string name);

  std::optional<Account> ReadAccount(std::string number);

  bool save(Account& account);

  bool DeleteAccount(Account& account);

private:
  static std::uint64_t nextId();

  Poco::Data::Session& m_session;
};
} // namespace db