#pragma once
#include <optional>

#include <Poco/Data/Session.h>

#include "account.hpp"

namespace db {
class AccountDAO { //deals with database (Database Access Object)
public:
  explicit AccountDAO(Poco::Data::Session& session);

  std::optional<Account> CreateAccount(std::string name);

  std::optional<Account> ReadAccountByNumber(std::string number);
  std::optional<Account> ReadAccountByName(std::string holderName);

  void ReadAllAccounts();

  bool Save(Account& account);

  bool DeleteAccount(Account& account);

private:
  static std::uint64_t nextId();

  Poco::Data::Session& m_session;
};
} // namespace db