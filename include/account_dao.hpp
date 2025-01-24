#pragma once
#include <optional>

#include <Poco/Data/Session.h>

#include "account.hpp"

namespace db {
class AccountDAO { //deals with database (Database Access Object)
public:
  explicit AccountDAO(Poco::Data::Session& session);

  std::unique_ptr<Account> CreateAccount(std::string name, std::string type);
  std::unique_ptr<Account> CreateAccountObject(std::string type, std::string number, std::string name, double interestRate, double balance);

  std::unique_ptr<Account> ReadAccountByNumber(std::string number);
  std::unique_ptr<Account> ReadAccountByName(std::string holderName);
  std::optional<Account> CheckAccountType(std::string type);

  bool Save(Account& account);

  bool DeleteAccount(Account& account);
  bool UpdateAccount(Account& account, std::string newName);
  Poco::Data::Session& GetSession() { return m_session; }

private:
  static std::uint64_t nextId();

  Poco::Data::Session& m_session;
};
} // namespace db