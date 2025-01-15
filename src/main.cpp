#include <iostream>

#include <Poco/Data/MySQL/Connector.h>
#include <Poco/Data/Session.h>
#include <Poco/Data/SessionFactory.h>

#include "account_dao.hpp"
#include "scope_guard.hpp"
#include "account.hpp"

enum class Options : int
{
  CREATE_ACCOUNT = 1,
  DEPOSIT_MONEY,
  WITHDRAW_MONEY,
  READ_ACCOUNT,
  UPDATE_ACCOUNT,
  DELETE_ACCOUNT
};

std::istream& operator>>(std::istream& is, Options& options)
{
  int buffer{0};
  is >> buffer;
  if (!is) {
    return is;
  }
  if (buffer < 1 || buffer > 6) {
    is.setstate(std::ios_base::failbit);
    return is;
}

options = static_cast<Options>(buffer);
return is;
}


int main()
{
  Poco::Data::MySQL::Connector::registerConnector();
  const std::string connectionString{
    "host=127.0.0.1;user=root;password=Patrycja1234;db=accountdb;compress=true;auto-"
    "reconnect="
    "true"};
  Poco::Data::Session session{Poco::Data::SessionFactory::instance().create(
    Poco::Data::MySQL::Connector::KEY, connectionString)};

  if (!session.isConnected()) {
    std::cerr << "session is not connected!\n";
    return EXIT_FAILURE;
  }

  if (!session.isGood()) {
    std::cerr << "session is bad!\n";
    return EXIT_FAILURE;
  }

  auto scopeGuard{db::makeScopeGuard([&session] {
    session.commit();
    session.close();
  })};

  Options option;

  std::cout << "Choose one of the option" << std::endl;
  std::cout << "1. Create Account" << std::endl;
  std::cout << "2. Deposit Money" << std::endl;
  std::cout << "3. Withdraw Money" << std::endl;
  std::cout << "4. Read Account" << std::endl;
  std::cout << "5. Update Account" << std::endl;
  std::cout << "6. Delete Account" << std::endl;
  std::cin >> option;

  db::AccountDAO accountDAO{session};

  switch (option)
  {
    case Options::CREATE_ACCOUNT:
    {
      std::string name;
      std::string surname;
      std::string type;

      std::cout << "Enter name: ";
      std::cin >> name;
      std::cout << "Enter surname: ";
      std::cin >> surname;
      std::cout << "Enter account type: ";
      std::cin >> type;
      
      std::optional<db::Account> optionalAccount{
        accountDAO.CreateAccount(name + " " + surname, type)};


      if (!optionalAccount.has_value()) {
        std::cerr << "Couldn't create new user!\n";
        return EXIT_FAILURE;
      }

      db::Account& account{*optionalAccount};
      std::cout << "Successfully created \"" << account << "\"!\n";
      break;
    }
    case Options::DEPOSIT_MONEY:
    {
      std::string name;
      std::string surname;

      std::cout << "Enter holder name: ";
      std::cin >> name;
      std::cout << "Enter surname: ";
      std::cin >> surname;

      std::unique_ptr<db::Account> optional = accountDAO.ReadAccountByName(name + " " + surname);

      if (!optional) {
        std::cerr << "Couldn't find client with name " << name + " " + surname << "\n";
        return EXIT_FAILURE;
      }

      double amount;

      std::cout << "Enter amount: ";
      std::cin >> amount;
  
      optional.get()->DepositMoney(amount);

      break;
    }
    case Options::WITHDRAW_MONEY:
    {
      std::string name;
      std::string surname;

      std::cout << "Enter holder name: ";
      std::cin >> name;
      std::cout << "Enter surname: ";
      std::cin >> surname;

      std::unique_ptr<db::Account> optional = accountDAO.ReadAccountByName(name + " " + surname);

      if (!optional) {
        std::cerr << "Couldn't find client with name " << name + " " + surname << "\n";
        return EXIT_FAILURE;
      }

      double amount;

      std::cout << "Enter amount: ";
      std::cin >> amount;
  
      optional->WithdrawMoney(amount);
      break;
    }
    case Options::READ_ACCOUNT:
    {
      int option;
      std::cout << "Choose read option 1 (by number), 2 (by name)" << std::endl;
      std::cin >> option;

      if (option == 1)
      {
        std::string number;
        std::cout << "Enter account number: ";
        std::cin >> number;

        std::unique_ptr<db::Account> optional{accountDAO.ReadAccountByNumber(number)};

        if (!optional) {
          std::cerr << "Couldn't find client with number " << number << "\n";
          return EXIT_FAILURE;
        }
      }
      else if (option == 2)
      {
        std::string name;
        std::string surname;

        std::cout << "Enter holder name: ";
        std::cin >> name;
        std::cout << "Enter surname: ";
        std::cin >> surname;

        std::unique_ptr<db::Account> optional{accountDAO.ReadAccountByName(name + " " + surname)};

        if (!optional) {
          std::cerr << "Couldn't find client with name " << name + " " + surname << "\n";
          return EXIT_FAILURE;
        }
      }
      else
      {
        std::cerr << "Wrong option\n";
        return EXIT_FAILURE;
      }

      break;
    }
    // case Options::UPDATE_ACCOUNT:
    // {
    //   int option;
    //   std::cout << "Choose read option 1 (by number), 2 (by name)" << std::endl;
    //   std::cin >> option;

    //   if (option == 1)
    //   {
    //     std::string number;
    //     std::cout << "Enter account number: ";
    //     std::cin >> number;

    //     std::optional<db::Account> optional{accountDAO.ReadAccountByNumber(number)};

    //     if (!optional.has_value())
    //     {
    //       std::cerr << "Couldn't find client with account number " << number << "\n";
    //       return EXIT_FAILURE;
    //     }
    //     else
    //     {
    //       std::string newName;
    //       std::string surname;

    //       std::cout << "Enter new name: ";
    //       std::cin >> newName;
    //       std::cout << "Enter new surname: ";
    //       std::cin >> surname;

    //       accountDAO.UpdateAccount(*optional, newName + " " + surname);
    //     }
    //   }
    //   else if (option == 2)
    //   {
    //     std::string name;
    //     std::string surname;

    //     std::cout << "Enter holder name: ";
    //     std::cin >> name;
    //     std::cout << "Enter surname: ";
    //     std::cin >> surname;

    //     std::optional<db::Account> optional{accountDAO.ReadAccountByName(name + " " + surname)};

    //     if (!optional.has_value()) {
    //       std::cerr << "Couldn't find client with name " << name + " " + surname << "\n";
    //       return EXIT_FAILURE;
    //     }
    //     else
    //     {
    //       std::string newName;
    //       std::string surname;

    //       std::cout << "Enter new name: ";
    //       std::cin >> newName;
    //       std::cout << "Enter new surname: ";
    //       std::cin >> surname;

    //       accountDAO.UpdateAccount(*optional, newName + " " + surname);
    //     }
    //   }
    //   else
    //   {
    //     std::cerr << "Wrong option\n";
    //     return EXIT_FAILURE;
    //   }
    //   break;
    // }
    // case Options::DELETE_ACCOUNT:
    // {
    //   int option;
    //   std::cout << "Choose read option 1 (by number), 2 (by name)" << std::endl;
    //   std::cin >> option;

    //   if (option == 1)
    //   {
    //     std::string number;
    //     std::cout << "Enter account number: ";
    //     std::cin >> number;

    //     std::optional<db::Account> optional{accountDAO.ReadAccountByNumber(number)};

    //     if (!optional.has_value())
    //     {
    //       std::cerr << "Couldn't find client with account number " << number << "\n";
    //       return EXIT_FAILURE;
    //     }
    //     else
    //     {
    //       accountDAO.DeleteAccount(*optional);
    //       std::cout << "Account deleted\n";
    //     }
    //   }
    //   else if (option == 2)
    //   {
    //     std::string name;
    //     std::string surname;

    //     std::cout << "Enter holder name: ";
    //     std::cin >> name;
    //     std::cout << "Enter surname: ";
    //     std::cin >> surname;

    //     std::optional<db::Account> optional{accountDAO.ReadAccountByName(name + " " + surname)};

    //     if (!optional.has_value()) {
    //       std::cerr << "Couldn't find client with name " << name + " " + surname << "\n";
    //       return EXIT_FAILURE;
    //     }
    //     else
    //     {
    //       accountDAO.DeleteAccount(*optional);
    //       std::cout << "Account deleted\n";
    //     }
    //   }
    //   else
    //   {
    //     std::cerr << "Wrong option\n";
    //     return EXIT_FAILURE;
    //   }
    // }
    
  default:
    break;
  }

 
  return EXIT_SUCCESS;
}
