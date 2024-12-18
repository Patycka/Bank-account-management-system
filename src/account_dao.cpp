#include <atomic>

#include "account_dao.hpp"

namespace db {
using namespace Poco::Data::Keywords;

AccountDAO::AccountDAO(Poco::Data::Session& session) : m_session{session}
{
}

std::optional<Account> AccountDAO::CreateAccount(std::string name)
{
  try {
    std::string number = "120390248924809284022482"; // @todo write generator for account number
    Account account{number, std::move(name)}; // check move description
    Poco::Data::Statement insertStatement{m_session};

    insertStatement << "INSERT INTO clients VALUES (?, ?, ?)", use(account.m_accountNumber), use(account.m_accountHolderName), use(account.m_balance);
    const std::size_t rowsAffected{insertStatement.execute()};
    std::cerr << "Try!\n";

    if (rowsAffected == 0) {
      std::cerr << "rowsAffected == 0!\n";
      return std::nullopt;
    }

    if (!insertStatement.done()) {
      std::cerr << "insertStatement.done()!\n";
      return std::nullopt;
    }

    return account;
  }
  catch ([[maybe_unused]] const Poco::Exception& exception) {
    std::cout << exception.message() << std::endl; 
    return std::nullopt;
  }
}

std::optional<Account> AccountDAO::ReadAccount(std::string number)
{
  try {
    Poco::Data::Statement selectStatement{m_session};
    std::string           holder_name{};
    selectStatement << "SELECT holder_name FROM clients WHERE account_number=?", into(holder_name), use(number);
    const std::size_t rowsAffected{selectStatement.execute()};

    if (rowsAffected == 0) {
      return std::nullopt;
    }

    if (!selectStatement.done()) {
      return std::nullopt;
    }

    return Account{number, std::move(holder_name)};
  }
  catch ([[maybe_unused]] const Poco::Exception& exception) {
    return std::nullopt;
  }
}

// bool AccountDAO::UpdateAccount(Account& Account, std::string newName)
// {
//   try {
//     Poco::Data::Statement updateStatement{m_session};
//     updateStatement << "UPDATE Account SET name=? WHERE id=?", use(newName),
//       use(Account.m_id);
//     const std::size_t rowsAffected{updateStatement.execute()};

//     if (rowsAffected == 0) {
//       return false;
//     }

//     if (!updateStatement.done()) {
//       return false;
//     }

//     Account.m_name = std::move(newName);
//     return true;
//   }
//   catch ([[maybe_unused]] const Poco::Exception& exception) {
//     return false;
//   }
// }

bool AccountDAO::DeleteAccount(Account& account)
{
  try {
    Poco::Data::Statement deleteStatement{m_session};
    deleteStatement << "DELETE FROM clients where account_number=?", use(account.m_accountNumber);
    const std::size_t rowsAffected{deleteStatement.execute()};

    if (rowsAffected == 0) {
      return false;
    }

    if (!deleteStatement.done()) {
      return false;
    }

    account.m_accountNumber.clear();
    account.m_accountHolderName.clear();
    account.m_balance = 0;
    return true;
  }
  catch ([[maybe_unused]] const Poco::Exception& exception) {
    return false;
  }
}

// std::uint64_t AccountDAO::nextId()
// {
//   static std::atomic<std::uint64_t> id{1};
//   return id++;
// }
} // namespace db
