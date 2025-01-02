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
    Account account{number, std::move(name), *this}; // check move description
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

std::optional<Account> AccountDAO::ReadAccountByNumber(std::string number)
{
  try {
    Poco::Data::Statement selectStatement{m_session};
    std::string           holder_name{};
    double                balance{};
    selectStatement << "SELECT holder_name, balance FROM clients WHERE account_number=?", into(holder_name), into(balance), use(number);
    const std::size_t rowsAffected{selectStatement.execute()};

    if (rowsAffected == 0) {
      return std::nullopt;
    }

    if (!selectStatement.done()) {
      return std::nullopt;
    }

    return Account{number, std::move(holder_name), *this, balance};
  }
  catch ([[maybe_unused]] const Poco::Exception& exception) {
    return std::nullopt;
  }
}

std::optional<Account> AccountDAO::ReadAccountByName(std::string holderName)
{
  try {
    Poco::Data::Statement selectStatement{m_session};
    std::string           number{};
    double                balance{};
    selectStatement << "SELECT account_number, balance FROM clients WHERE holder_name=?", into(number), into(balance), use(holderName);
    const std::size_t rowsAffected{selectStatement.execute()};

    if (rowsAffected == 0) {
      return std::nullopt;
    }

    if (!selectStatement.done()) {
      return std::nullopt;
    }

    return Account{number, std::move(holderName), *this, balance};
  }
  catch ([[maybe_unused]] const Poco::Exception& exception) {
    return std::nullopt;
  }
}

bool AccountDAO::Save(Account& account)
{
  try {
    Poco::Data::Statement updateStatement{m_session};
    updateStatement << "UPDATE clients SET holder_name = ?, balance = ? WHERE account_number=?", use(account.m_accountHolderName), 
    use(account.m_balance), use(account.m_accountNumber);
    const std::size_t rowsAffected{updateStatement.execute()};

    if (rowsAffected == 0) {
      return false;
    }

    if (!updateStatement.done()) {
      return false;
    }

    return true;
  }
  catch ([[maybe_unused]] const Poco::Exception& exception) {
    return false;
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

// std::optional<Account> AccountDAO::DepositMoney(std::string number, double amount)
// {
//   try {
//     Poco::Data::Statement updateStatement{m_session};
//     updateStatement << "UPDATE clients SET balance=balance+? WHERE account_number=?", use(amount), use(number);
//     const std::size_t rowsAffected{updateStatement.execute()};

//     if (rowsAffected == 0) {
//       return std::nullopt;
//     }

//     if (!updateStatement.done()) {
//       return std::nullopt;
//     }

//     return ReadAccount(number);
//   }
//   catch ([[maybe_unused]] const Poco::Exception& exception) {
//     return std::nullopt;
//   }
// }

// std::optional<Account> AccountDAO::WithdrawMoney(std::string number, double amount)
// {
//   try {
//     Poco::Data::Statement updateStatement{m_session};
//     updateStatement << "UPDATE clients SET balance=balance-? WHERE account_number=?", use(amount), use(number);
//     const std::size_t rowsAffected{updateStatement.execute()};

//     if (rowsAffected == 0) {
//       return std::nullopt;
//     }

//     if (!updateStatement.done()) {
//       return std::nullopt;
//     }

//     return ReadAccount(number);
//   }
//   catch ([[maybe_unused]] const Poco::Exception& exception) {
//     return std::nullopt;
//   }
// }

void AccountDAO::ReadAllAccounts()
{
  try {
    Poco::Data::Statement selectStatement{m_session};
    std::string           number{};
    std::string           holder_name{};
    double                balance{};
    selectStatement << "SELECT * FROM clients", into(number), into(holder_name), into(balance);
    const std::size_t rowsAffected{selectStatement.execute()};

    if (rowsAffected == 0) {
      //return std::nullopt;
    }

    if (!selectStatement.done()) {
      //return std::nullopt;
    }

    //return Account{number, std::move(holder_name), balance};
  }
  catch ([[maybe_unused]] const Poco::Exception& exception) {
    //return std::nullopt;
  }
}
} // namespace db
