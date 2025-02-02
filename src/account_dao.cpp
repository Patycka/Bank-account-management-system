#include <atomic>

#include "account_dao.hpp"
#include "checking_account.hpp"
#include "helpers/random_digit_generator.hpp"
#include "savings_account.hpp"

namespace db {
using namespace Poco::Data::Keywords;

AccountDAO::AccountDAO(Poco::Data::Session& session) : m_session{session}
{
}

std::unique_ptr<Account> AccountDAO::CreateAccount(std::string name, std::string type)
{
  try {
    int accountLength = 10;
    std::string number = helper::GenerateRandomDigits(accountLength);
    std::unique_ptr<Account> account = CreateAccountObject(type, number, name, 0, 0);
    Poco::Data::Statement insertStatement{m_session};

    insertStatement << "INSERT INTO clients VALUES (?, ?, ?, ?, ?)", 
                    use(account->m_accountNumber),
                    use(account->m_accountHolderName),
                    use(account->m_balance),
                    use(account->m_type),
                    use(account->m_interestRate);

    const std::size_t rowsAffected{insertStatement.execute()};
    std::cerr << "Try!\n";

    if (rowsAffected == 0) {
      std::cerr << "rowsAffected == 0!\n";
      return nullptr;
    }

    if (!insertStatement.done()) {
      std::cerr << "insertStatement.done()!\n";
      return nullptr;
    }

    return account;
  }
  catch ([[maybe_unused]] const Poco::Exception& exception) {
    std::cout << exception.message() << std::endl; 
    return nullptr;
  }
}


std::unique_ptr<Account> AccountDAO::CreateAccountObject(std::string type, std::string number, std::string name, double interestRate, double balance) 
{
  if (type == "Checking") {
       return std::make_unique<CheckingAccount>(number, name, *this, interestRate);
  } 
  else if (type == "Savings") {
    return std::make_unique<SavingsAccount>(number, name, *this, interestRate, balance);
  }
  else if (type == "Default") {
    return std::make_unique<Account>(number, name, *this, balance);
  }
  else {
    throw std::runtime_error{"Invalid type: " + type + "!"};
  }
}


std::optional<Account> AccountDAO::CheckAccountType(std::string type)
{
  try {
    Poco::Data::Statement selectStatement{m_session};
    std::string           number{};
    std::string           holder_name{};
    double                balance{};
    std::string           account_type{};
    selectStatement << "SELECT * FROM clients WHERE type=?", into(number), into(holder_name), into(balance), into(account_type), use(type), range(0, 1);
    const std::size_t rowsAffected{selectStatement.execute()};

    if (rowsAffected == 0) {
      return std::nullopt;
    }

    while (!selectStatement.done())
    {
        selectStatement.execute();
    }

    
    return Account{number, std::move(holder_name), *this, balance};
  }
  catch ([[maybe_unused]] const Poco::Exception& exception) {
    return std::nullopt;
  }
}

std::unique_ptr<Account> AccountDAO::ReadAccountByNumber(std::string number)
{
  try {
    Poco::Data::Statement selectStatement{m_session};
    std::string           holderName{};
    double                balance{};
    std::string           type{};
    selectStatement << "SELECT holder_name, balance, account_type FROM clients WHERE account_number=?", 
                        into(holderName), 
                        into(balance),
                        into(type),
                        use(number), 
                        range(0, 1);
    const std::size_t rowsAffected{selectStatement.execute()};

    if (rowsAffected == 0) {
      return nullptr;
    }

    while (!selectStatement.done())
    {
        selectStatement.execute();
        std::cout << "Number " << number << " Name " << holderName << " Balance " << balance << std::endl;
    }

    std::cout << "Number " << number << " Name " << holderName << " Balance " << balance << std::endl;
    return CreateAccountObject(type, number, holderName, 0, balance);
  }
  catch ([[maybe_unused]] const Poco::Exception& exception) {
    return nullptr;
  }
}

std::unique_ptr<Account> AccountDAO::ReadAccountByName(std::string holderName)
{
  try {
    Poco::Data::Statement selectStatement{m_session};
    std::string           number{};
    double                balance{};
    std::string           type{};
    selectStatement << "SELECT account_number, balance, account_type FROM clients WHERE holder_name=?", 
                      into(number), 
                      into(balance),
                      into(type),
                      use(holderName),
                      range(0, 1);
    const std::size_t rowsAffected{selectStatement.execute()};

    if (rowsAffected == 0) {
      return nullptr;
    }

    while (!selectStatement.done())
    {
        selectStatement.execute();
        std::cout << "Number " << number << " Name " << holderName << " Balance " << balance << " Type " << type << std::endl;
    }

    std::cout << "Number " << number << " Name " << holderName << " Balance " << balance << std::endl;
    return CreateAccountObject(type, number, holderName, 0, balance);
  }
  catch ([[maybe_unused]] const Poco::Exception& exception) {
    return nullptr;
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

bool AccountDAO::UpdateAccount(Account& Account, std::string newName)
{
  try {
    Poco::Data::Statement updateStatement{m_session};
    updateStatement << "UPDATE clients SET holder_name=? WHERE holder_name=?", use(newName),
      use(Account.m_accountHolderName);
    const std::size_t rowsAffected{updateStatement.execute()};

    if (rowsAffected == 0) {
      return false;
    }

    if (!updateStatement.done()) {
      return false;
    }

    Account.m_accountHolderName = std::move(newName);
    return true;
  }
  catch ([[maybe_unused]] const Poco::Exception& exception) {
    return false;
  }
}

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

} // namespace db
